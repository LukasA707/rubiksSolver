import twophase.solver  as sv
import cubotino_solver as cs
import twophase.cubie as cubie
import commands_enum as commands_enum 
import serial

# Code for running the rubiks cube solver. 
# Credit for the rubiks cube solving algorithm to Herbert Kociemba
#   at https://github.com/hkociemba/RubiksCube-TwophaseSolver
# And credit for translating those instructions to a robot that only supports flipping and turning one side of the cube
# to Andre Favero at https://github.com/AndreaFavero71/cubotino

Command = commands_enum.Command
SOLVE_TIMEOUT = 2 # how long to spend running the solve algorithm (seconds)
SERIAL_PORT = ""
SERIAL_BAUDRATE = 9600

CUBE_STRING = "".join([
"DUDFUUBUU",    ## UP       WHITE
"LBLDRBUFF"     ## RIGHT    ORANGE     
"RRBLFRFBF"     ## FRONT    BLUE
"LRRFDLFFL"     ## DOWN     YELLOW
"RDUDLDDUU"     ## LEFT     RED
"BLBLBBDRR"     ## BEHIND   GREEN
])

ser = serial.Serial(port=SERIAL_PORT, baudrate=SERIAL_BAUDRATE)

#######################################
## Demo on a randomly generated cube
## cube_string is a string representing the cube. this is what we should hardcode if we enter cube config manually
## see here for description of string representation: https://github.com/hkociemba/RubiksCube-TwophaseSolver
# cube = cubie.CubieCube()
# cube.randomize()
# fc = cube.to_facelet_cube()
# CUBE_STRING = fc.to_string()
# cube_solution_1 = 'U2 L1 R1 D2 B2 R1 D2 B2 D2 L3 B3 R3 F2 D3 L1 U2 F2 D3 B3 D1' # cube solution that allows type 1 optimization
# cube_solution_2 = 'U2 D2 R2 L2 F2 B2' # cube solution that allows type 2 optimization

#### Testing / debugging functions
def revert_solution():
    solved_cube = 'UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB'
    solution = sv.solveto(solved_cube, CUBE_STRING, 0, SOLVE_TIMEOUT)
    return solution[:solution.find('(')]

def debug_cube_string():
    for c in 'URFDLB':
        print(f'Count of {c} in string: {CUBE_STRING.count(c)}')

def debug_print(robot, moves, total_moves, opt):
    print(f'\nnumber of robot movements: {total_moves}')

    print()    
    print(f'robot movements: ')
    servo_moves=""
    for step, movements in robot.items():
        print(f'step:{step}, robot moves:{movements}')
        servo_moves+=movements

    print(f'\npossible optimizers used?: {opt}\n')
    print(f'\nservo_moves: {servo_moves}\nidentical? {servo_moves == moves}')
    print(f'\nstring command to the robot servos driver: {moves}\n')
###########################################################################

def parse_cubotino_step(step):
    (cmd, num) = (step[0], int(step[1]))
    if cmd == 'S':
        if num == 0 or num == 4:
            return [Command.SPIN_FULL]
        if num == 1:
            return [Command.SPIN_CW_HALF]
        if num == 3:
            return [Command.SPIN_CCW_HALF]
    elif cmd == 'R':
        if num == 0 or num == 4:
            return [Command.TURN_FULL]
        if num == 1:
            return [Command.TURN_CW_HALF]
        if num == 3:
            return [Command.TURN_CCW__HALF]
    elif cmd == 'F':
        return [Command.FLIP for _ in range(num)]
    
def send_command(cmd: str):
    # print(f'sending to serial: {cmd}')
    # return
    ser.write(cmd.encode('utf-8'))
    while True:
        result = str(ser.readline())
        if (result != f'{cmd}_ok'):
            # possibly handle error from arduino?
            pass
        return


def parse_solution(solution_string):
    # solution for robot based on cubotino solver. we just use the unoptimized moves (in robot dict)
    robot, moves, robot_tot_moves, opt = cs.robot_required_moves(solution_string, '', True, False)
    # debug_print(robot, moves, robot_tot_moves, opt)
    arduino_steps = []

    for step, movement in robot.items():
        cubo_movements = [movement[i:i+2] for i in range(0, len(movement), 2)]
        converted_movements = sum(list(map(parse_cubotino_step, cubo_movements)), [])
        arduino_steps.append(converted_movements)
        # print(movement)
        # for m in converted_movements:
        #     print(m)
        # print()
    
    return arduino_steps

if __name__ == "__main__":
    sol = sv.solve(CUBE_STRING, 0, SOLVE_TIMEOUT)
    sol = sol[:sol.find('(')] # solution string also includes number of moves, we only want the move sequence
    if ('Error' in sol):
        debug_cube_string()
        raise Exception(f'There was an error solving the cube. Error is:\n{sol}')

    arduino_steps = parse_solution(sol)
    # arduino_steps = parse_solution(revert_solution())
    # print(revert_solution())

    for idx, step in enumerate(arduino_steps):
        print(f'Running step {idx}')
        for movement in step:
            send_command(movement)