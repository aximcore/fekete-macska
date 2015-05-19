package me.aximcore;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import me.aximcore.Lap;

public class Main {

    public static void main(String[] args) {
        Jatekos jatekos = new Jatekos();
        int portNumber = 5000;
        String temp;
        try(Socket socket1 = new Socket("localhost", portNumber);
            InputStream in = socket1.getInputStream();
            OutputStream out = socket1.getOutputStream();
            BufferedWriter bufOut = new BufferedWriter( new OutputStreamWriter( out ) );
        )
        {

            Scanner sc = new Scanner(in);

            if(sc.hasNextLine())
                jatekos.setId(sc.nextLine());

        //while(true){
            if(sc.hasNextLine()) {
                temp = sc.nextLine(); // paklim
                String[] l = temp.split("(\\s)*;+(\\s)*");
                for( int i = 1; i < l.length - 1; i += 2) {
                    if(!l[i].matches("") && !l[i + 1].matches(""))
                        jatekos.lapok.add(new Lap(Integer.parseInt(l[i]), Integer.parseInt(l[i + 1]), false));
                }
            }

            if(sc.hasNextLine()){
                jatekos.kezdoJatekos = sc.nextLine();

            }
            boolean elso = true;

            do{

                if (sc.hasNextLine()) {
                    String korok = sc.nextLine();
                    if (elso && jatekos.isKezdo()) {
                        System.out.println("Első kör megkezdese");
                        System.out.println("Én kezdem a jatekot!");
                        bufOut.write(";00;02;");//jatekos.getLapStr(Lap.Rang.ketto, Lap.Szin.treff));
                        bufOut.newLine();
                        bufOut.flush();
                        elso = !elso;
                    } else {
                        System.out.println(jatekos.kezdoJatekos + " kezdi a jatekot.\n" + korok);
                        System.out.println("index\t\trang;szin");
                        System.out.println(jatekos.getLapjaim()+"\nf feladas, vagy valaszon indexet");
                        String lapom = System.console().readLine();

                        if(lapom.matches("f")){
                        	bufOut.write(lapom);
                            bufOut.newLine();
                        	bufOut.flush();
                        } else {
                            bufOut.write(jatekos.getLap((Integer.parseInt(lapom))).toString());
                            bufOut.newLine();
                            bufOut.flush();
                        }
                    }


                    for(int i = 0; i < 4; i++)
                        if(sc.hasNextLine()){
                            String kirakot = sc.nextLine();
                            System.out.println(kirakot); // ki mit rak le

                            if(kirakot.matches("f")){
                                System.out.println("Mas feladta kilepes !");
                            	/*System.out.println("Mas feladta uj jatek kezdese ?");
                                String be = System.console().readLine();
                                if ( be.matches("i") ){
                                    bufOut.write("i");
                                    bufOut.newLine();
                                    bufOut.flush();
                                    //main(args);
                                } else { */
                                    System.exit(0);
                                //}
                            }
                        }

                    /*if ( sc.hasNextLine() ){
                        String vege = sc.nextLine();
                        if(vege.matches("vege")){
                            System.out.println("Ujat kezd vagy kilep ? u - k");
                            String be = System.console().readLine();
                            if ( be.matches("u") ){
                                main(args);
                            } else {
                                System.exit(0);
                            }

                        }
                    }*/

                }
            }while(true);


            /*if( sc.hasNextLine() ){
                if(sc.nextLine().matches("vege")){
                    System.out.println("Vege, ujra ? t - f");
                    String vege = System.console().readLine();
                    bufOut.write(vege);
                    bufOut.flush();

                    if (vege == "f"){
                        System.exit(0);
                    }
                }
            }*/

        //} // while end

        } catch (IOException e){
            System.out.println(e.toString());
        }

    }
}
