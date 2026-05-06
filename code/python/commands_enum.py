from enum import StrEnum

class Command(StrEnum):
  SPIN_CW_HALF = "spin_cw_half"
  SPIN_CCW_HALF = "spin_ccw_half"
  SPIN_FULL = "spin_full"
  TURN_CW_HALF = "turn_cw_half"
  TURN_CCW__HALF = "turn_ccw__half"
  TURN_FULL = "turn_full"
  FLIP = 'flip'
