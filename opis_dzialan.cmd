
#define samochod Podstawa
#define kolo1 Podstawa.Kolo1
#define kolo2 Podstawa.Kolo2
#define kolo3 Podstawa.Kolo3
#define kolo4 Podstawa.Kolo4
#define predkosc_kat -240
#define predkosc_kat2 240
#define kat_ob 1440
#define kat_ob1 480
#define kat_ob2 720
#define czas 2000

Begin_Parallel_Actions
Set samochod 2 -2 1 30 0 0
End_Parallel_Actions

Begin_Parallel_Actions
Move samochod 0.5 3  
Rotate kolo1 predkosc_kat x kat_ob
Rotate kolo2 predkosc_kat x kat_ob
Rotate kolo3 predkosc_kat x kat_ob
Rotate kolo4 predkosc_kat x kat_ob
End_Parallel_Actions

Begin_Parallel_Actions
Pause czas  
End_Parallel_Actions

Begin_Parallel_Actions
Rotate samochod -15 x 30
Rotate kolo1 predkosc_kat x kat_ob1
Rotate kolo2 predkosc_kat x kat_ob1
End_Parallel_Actions

Begin_Parallel_Actions
Pause czas  
End_Parallel_Actions

Begin_Parallel_Actions
Rotate samochod 30 z 90
Rotate kolo1 predkosc_kat x kat_ob2
Rotate kolo2 predkosc_kat2 x kat_ob2
Rotate kolo3 predkosc_kat2 x kat_ob2
Rotate kolo4 predkosc_kat x kat_ob2
End_Parallel_Actions


