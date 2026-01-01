#define NRANGES 4
#define NINGRIDIENTS 6

typedef struct range_t {
  long start;
  long end;
} range_t;

range_t ranges[NRANGES] = {
    {3, 5},
    {10, 14},
    {16, 20},
    {12, 18},
};

long ingridients[NINGRIDIENTS] = {
    1, 5, 8, 11, 17, 32,
};
