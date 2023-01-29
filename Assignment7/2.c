 #include <stdio.h>

 typedef struct {
		int D_Geburtsjahr;
        int Anzahl_m;
        // Die durchschnittliche Körpergröße der Männer, Die durchschnittliche Körpergröße der Frauen.
	 }Statistics;
	 
// b) ... make_statistics...
    int f(){
	Statistics list ;
    list.D_Geburtsjahr = 5;
    list.Anzahl_m = 3;
    printf("%d",list.D_Geburtsjahr);
    printf("%d",list.Anzahl_m);
		return 0;
	}
    int main(){
        f();
        return 0;
    }