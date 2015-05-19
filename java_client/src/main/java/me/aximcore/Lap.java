package me.aximcore;

/**
 * Created by aximcore on 2015.05.18..
 */
public class Lap {
    Lap(){}

    Lap(Integer rang, Integer szin, boolean hasznalt){
        if(rang == 0)
            this.rang = Rang.ketto;
        if(rang == 1)
            this.rang = Rang.harom;
        if(rang == 2)
            this.rang = Rang.negy;
        if(rang == 3)
            this.rang = Rang.ot;
        if(rang == 4)
            this.rang = Rang.hat;
        if(rang == 5)
            this.rang = Rang.het;
        if(rang == 6)
            this.rang = Rang.nyolc;
        if(rang == 7)
            this.rang = Rang.kilenc;
        if(rang == 8)
            this.rang = Rang.tiz;
        if(rang == 9)
            this.rang = Rang.j;
        if(rang == 10)
            this.rang = Rang.q;
        if(rang == 11)
            this.rang = Rang.k;
        if(rang == 12)
            this.rang = Rang.a;

        if(szin == 0)
            this.szin = Szin.pikk;
        if(szin == 1)
            this.szin = Szin.karo;
        if(szin == 2)
            this.szin = Szin.treff;
        if(szin == 3)
            this.szin = Szin.kor;

        this.hasznalt = hasznalt;
    }
    Szin szin;
    Rang rang;
    boolean hasznalt;

    enum Szin {
        pikk(0),karo(1),treff(2),kor(3);
        final int value;

        Szin(int value){
            this.value = value;
        }

        public int getValue(){return value;}
    }

    public enum Rang {
        ketto(0),   harom(1),
        negy(2),    ot(3),
        hat(4),     het(5),
        nyolc(6),   kilenc(7),
        tiz(8),     j(9),
        q(10),      k(11),
        a(12);

        final int value;

        Rang(int value){
            this.value = value;
        }
        public int getValue(){return value;}
    }

    public String toString(){
        return ((this.rang.getValue() < 10 ? ";0" : ";") + this.rang.getValue()  ) +  ";0" + this.szin.getValue() + ";";
    }

    public void setHasznalt(boolean hasznalt){this.hasznalt = hasznalt;}
    public boolean getHasznalt(){return this.hasznalt;}

}
