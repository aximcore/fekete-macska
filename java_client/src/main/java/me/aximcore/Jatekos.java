package me.aximcore;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by aximcore on 2015.05.18..
 */
public class Jatekos extends Lap {
    String id;
    String kezdoJatekos;
    List<Lap> lapok = new ArrayList<>();

    public void setId(String id) {this.id = id;}

    public boolean isKezdo(){
        return this.kezdoJatekos.matches(this.id);
    }

    public String getLapjaim(){
        String temp = ""; int i = 0;
        for( Lap l : lapok ){
            if(!l.getHasznalt())
                temp += i + ".\t-\t" + l.toString() + "\n";
            i++;
        }
        return temp;
    }

    public String getLapStr(Rang rang, Szin szin){
        for(Lap l : lapok){
            if(l.rang.toString().matches(rang.toString()) && l.szin.toString().matches(szin.toString())){
                return l.toString();
            }
        }
        return "Nem talaltam!";
    }

    public Lap getLap(Rang rang, Szin szin){
        for(Lap l : lapok){
            if(l.rang.toString().matches(rang.toString()) && l.szin.toString().matches(szin.toString())){
                l.setHasznalt(false);
                return l;
            }
        }
        return null;
    }

    public Lap getLap(int index){
        lapok.get(index).setHasznalt(true);
        return lapok.get(index);
    }
}
