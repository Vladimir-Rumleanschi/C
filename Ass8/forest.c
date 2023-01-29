#include "base.h"

#define WORLD_WIDTH 32
#define WORLD_HEIGHT 16
const String STRING_PLAYER = "☺";

typedef enum tiletype_e {
    TT_GRASS,
    TT_TREE,
    TT_EMERALD,
} TileType;

typedef struct gamestate_s {
    TileType world[WORLD_WIDTH * WORLD_HEIGHT];
    struct {
        unsigned x;
        unsigned y;
    } player;
    int collected_emeralds;
} Gamestate;

void clear() {
    printf("\33[2J");
}

String string_for_tile(TileType tile) {
    switch(tile) {
    case TT_GRASS:
        return " ";
    case TT_TREE:
        return "#";
    case TT_EMERALD:
        return "V";
    default:
        return "X";
    }
}

Gamestate make_gamestate() {
    return (Gamestate) {
        .player.x = WORLD_WIDTH / 2,
        .player.y = WORLD_HEIGHT / 2,
        .collected_emeralds = 0,
    };
}



TileType get_tile(Gamestate *gamestate, unsigned x, unsigned y) {
    // todo
    return (gamestate)->world[WORLD_WIDTH * y + x];
}

void set_tile(Gamestate *gamestate, unsigned x, unsigned y, TileType tile) {
    // todo
    (gamestate)->world[WORLD_WIDTH * y + x] = tile;
}

void generate_world(Gamestate *gamestate){
// todo

    for(int i = 0; i < WORLD_WIDTH * WORLD_HEIGHT;i++){

        int probabi =  rand() % 105;

        if( probabi >= 0 && probabi <= 5){
            (gamestate)->world[i] = TT_EMERALD;
        }else if (probabi >= 6 && probabi <= 20){
            (gamestate)->world[i] = TT_TREE;
        }else{
            (gamestate)->world[i] = TT_GRASS;
        }
    }
}

void draw(Gamestate gamestate) {
    // todo
    printc('\n');
    prints("--------------------------------\n");
    for (int i = 0; i < WORLD_WIDTH * WORLD_HEIGHT; i++){
        if (i == WORLD_WIDTH * (gamestate.player.y) + gamestate.player.x){
            prints("S");
        } else {
            prints(string_for_tile(gamestate.world[i]));
        }

        if(((i + 1) % WORLD_WIDTH == 0) && (i != 0) ){
            printc('\n');       

        }
    }
    
    prints("--------------------------------\n");
}

void move_player(Gamestate *gamestate, int dx, int dy) {
    // todo
    
    if( !(s_equals(string_for_tile(get_tile(gamestate,dx,dy)),"#")) ){
        if(dx < 0){
            (gamestate)->player.x = WORLD_WIDTH - 1;
        } else if(dx > WORLD_WIDTH - 1 && get_tile(gamestate, 0, (gamestate)->player.y) != TT_TREE){
            (gamestate)->player.x = 0;
        } else {
            (gamestate)->player.x = dx;
        }

        if(dy < 0){
            (gamestate)->player.y = WORLD_HEIGHT - 1 ;
        } else if(dy > WORLD_HEIGHT - 1 && get_tile(gamestate, (gamestate)->player.x, 0) != TT_TREE){
            (gamestate)->player.y = 0;
        } else {
            (gamestate)->player.y = dy;
        }

 
        if(s_equals(string_for_tile(get_tile(gamestate,dx,dy)),"V")){
            (gamestate)->collected_emeralds++;
            set_tile(gamestate,(gamestate)->player.x,(gamestate)->player.y,TT_GRASS);
        }
    }
}

int main(void) {
    Gamestate gamestate = make_gamestate();

    // todo
    String direction;

    generate_world(&gamestate);
    prints("Set a direction (u - up; v - down; < - left; > - right) \n");
    draw(gamestate);

    while(true){
       
        direction = s_input(10);
        if (s_equals(direction, "b")){ 
            printf("Giving up...");
            break;
        }
    
        if(s_equals(direction, "u")){
            move_player(&gamestate,gamestate.player.x,gamestate.player.y - 1);
        }else if (s_equals(direction, "v")){
            move_player(&gamestate, gamestate.player.x, gamestate.player.y + 1);
        }else if (s_equals(direction, ">")){
            move_player(&gamestate, gamestate.player.x + 1, gamestate.player.y);
        }else if (s_equals(direction, "<")){
            move_player(&gamestate, gamestate.player.x - 1, gamestate.player.y);
        }

        //clear();
        draw(gamestate);
        printf("You have collected %d emeralds \n",gamestate.collected_emeralds);
        prints("Set a direction (u - up; v - down; < - left; > - right) \n");
        if(gamestate.collected_emeralds == 5) {
            printf("You won the game!\n");
            break;
        }
    }

    return 0;
}
