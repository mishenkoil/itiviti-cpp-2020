#ifndef FIELD
#  error You need to define FIELD macro
#else
FIELD(time_in_force, 1, 1)
FIELD(capacity, 1, 8);
#undef FIELD
#endif
