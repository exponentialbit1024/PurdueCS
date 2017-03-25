/**
 * Created by sidshah on 3/1/17.
 */
public class Tester {

    public static void main(String[] args){
        Mustang m = new Mustang();
        FighterJet jet = new FighterJet();
        OilTanker o = new OilTanker();

        System.out.println(m.canFly()); //prints "false"
        System.out.println(jet.sonicBoom(550)); //prints "Whoosh!"
        System.out.println(jet.numWheels()); //prints '3'
        System.out.println(o.name()); //prints "Oil Tanker"
    }
}
