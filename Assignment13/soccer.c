/*
Compile: make soccer
Run: ./soccer < soccer_results.txt
make soccer && ./soccer < soccer_results.txt
*/

#include "map.h"

typedef struct Stats {
    int games_played;
    int goals_scored;
    int goals_received;
    int score;
} Stats;

Stats* new_stats(int played, int scored, int received, int score) {
    Stats* s = xcalloc(1, sizeof(Stats));
    s->games_played = played;
    s->goals_scored = scored;
    s->goals_received = received;
    s->score = score;
    return s;
} 

void free_stats(void* s) {
    free(s);
}

int hash_string(void* x) {
    String s = x;
    int n = s_length(s);
    int hash = 0;
    for (int i = 0; i < n; i++) {
        hash = hash * 31 + s[i];
    }
    if (hash < 0) hash = -hash;
    return hash;
}

void* copy_string(void* s) {
    return s_copy(s);
}

void free_string(void* s) {
    free(s);
}

bool strings_equal(void* x, void* y) {
    return s_equals(x, y);
}

int compare_teams(const void* a, const void* b) {
    const Entry* e1 = a;
    const Entry* e2 = b;
    // printf("e1->key = %s, e2->key = %s\n", e1->key, e2->key);
    // todo: implement (d)
    return 0;
}

int main(void) {
    report_memory_leaks(true);

    // m maps each team to its result
    Map* m = new_map(128, hash_string, strings_equal);
    while (true) {
        // todo: implement (a)
        String tnames1 = s_input(100);
        String tnames2 = s_input(100);
        if (tnames1 == NULL){
            free(tnames1);
            free(tnames2);
            break;
        }
        String g1 = s_input(100);
        String g2 = s_input(100);
        int goals1 = i_of_s(g1);
        int goals2 = i_of_s(g2);
        free(g1);
        free(g2);
        Stats* stati = get_map(m,tnames1);
        stati->games_played++;
        stati->goals_scored = stati->goals_scored + goals1;
        stati->goals_received = stati->goals_received +goals2;
        if (goals1 < goals2){
            stati->score = stati->score;
        } else if (goals1 > goals2 ){
            stati->score = stati->score + 3 ;
        } else {
            stati->score = stati->score + 1;
        }
    }

    
    Iterator* iter = new_iterator(m);
    while (has_next(iter)) {
        Entry e = next(iter);
        String team = e.key;
        Stats* s = e.value;
        printf("%s: played = %d, scored = %d, received = %d, score = %d\n", 
            team, s->games_played, s->goals_scored, s->goals_received, s->score);
    }
    free_iterator(iter);
    
    int n = size_map(m);
    Entry* entries = entries_map(m);
    if (n > 0 && entries != NULL) {
        // sort the entries according to the team scores
        qsort(entries, n, sizeof(Entry), compare_teams);
        for (int i = 0; i < n; i++) {
            Entry* e = entries + i;
            Stats* s = e->value;
            printf("%s: %d points\n", e->key, s->score);
        }
        free(entries);
    }
    free_map(m, free_string, free_stats);
}



