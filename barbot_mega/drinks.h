#define VODKA_PUMP  1
#define GIN_PUMP      2
#define RUM_PUMP   3
#define TEQUILA_PUMP   4
#define BOURBON_PUMP 5
#define KAHLUA_PUMP      6
#define LIME_PUMP   7
#define BLUE_CURACAO_PUMP    8
#define CRANBERRY_PUMP   9
#define AMARETTO_PUMP      10
#define BAILEYS_PUMP   11
#define ORANGE_PUMP  12
#define GRENADINE_PUMP   13
#define TRIPLE_SEC_PUMP      14
#define CAMPARI_PUMP   15
#define LEMON_PUMP  16
#define PINEAPPLE_PUMP      17
#define MALIBU_PUMP      18
#define SWEET_VERMOUTH_PUMP   19
#define SIMPLE_PUMP  20
#define PEACH_SCHNAPPS_PUMP      21

#define SPRITE_PUMP      22
#define GINGER_BEER_PUMP   23
#define SELTZER_PUMP  24


typedef struct drink {
    double mixersArray [24]={0};
    char * name, extras;
};
  
