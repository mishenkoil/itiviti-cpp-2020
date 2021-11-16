#if !defined(FIELD) || !defined(VAR_FIELD)
#  error You need to define FIELD and VAR_FIELD macro
#else

FIELD(capacity, char, char)
FIELD(time_in_force, char, char)

#undef FIELD
#undef VAR_FIELD

#endif
