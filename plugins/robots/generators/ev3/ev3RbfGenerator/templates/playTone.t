JR_EQ16(0, @@FREQUENCY@@, @@RANDOM_ID_1@@)
SOUND(TONE, @@VOLUME@@, @@FREQUENCY@@, @@DURATION@@)
JR_NEQ8(1, @@WAIT_FOR_COMPLETION@@, @@RANDOM_ID_2@@)
SOUND_READY
JR(@@RANDOM_ID_2@@)
@@RANDOM_ID_1@@:
JR_NEQ8(1, @@WAIT_FOR_COMPLETION@@, @@RANDOM_ID_2@@)
TIMER_WAIT(@@DURATION@@, timer)
TIMER_READY(timer)
@@RANDOM_ID_2@@:
