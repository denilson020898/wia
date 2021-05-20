(module

  (import "env" "_GenerateCards" 
    (func $GenerateCards (param i32 i32 i32)))

  (import "env" "_FlipCard" 
    (func $FlipCard (param i32 i32 i32)))

  (import "env" "_RemoveCards" 
    (func $RemoveCards (param i32 i32 i32 i32)))

  (import "env" "_LevelComplete" 
    (func $LevelComplete (param i32 i32)))

  (import "env" "_Pause" 
    (func $Pause (param i32 i32)))

  (import "env" "memory" 
    (memory $memory 256))

  (import "env" "_SeedRandomNumberGenerator" 
    (func $SeedRandomNumberGenerator))

  (import "env" "_GetRandomNumber" 
    (func $GetRandomNumber (param i32) (result i32)))

  (import "env" "_malloc"
    (func $malloc (param i32) (result i32)))

  (import "env" "_free"
    (func $free (param i32) (result i32)))

  (global $MAX_LEVEL i32 (i32.const 3))

  (global $cards (mut i32) (i32.const 0))
  (global $current_level (mut i32) (i32.const 0))
  (global $rows (mut i32) (i32.const 0))
  (global $columns (mut i32) (i32.const 0))
  (global $matches_remaining (mut i32) (i32.const 0))

  (global $first_card_row (mut i32) (i32.const 0))
  (global $first_card_column (mut i32) (i32.const 0))
  (global $first_card_value (mut i32) (i32.const 0))
  (global $second_card_row (mut i32) (i32.const 0))
  (global $second_card_column (mut i32) (i32.const 0))
  (global $second_card_value (mut i32) (i32.const 0))

  (global $execution_paused (mut i32) (i32.const 0))

  (export "_CardSelected"
    (func $CardSelected))

  (export "_SecondCardSelectedCallback"
    (func $SecondCardSelectedCallback))

  (export "_ReplayLevel"
    (func $ReplayLevel))

  (export "_PlayNextLevel"
    (func $PlayNextLevel))

  (start $main)

)
