/**
 * Created by sidshah on 4/21/17.
 */
public class Violin extends StringInstrument {
    public Violin(String musicianName){
        super(musicianName, 4);
    }

    public void play(String song){
        System.out.println(super.getMusicianName() + " is playing " + song + " on a " + super.getNumStrings() + " string violin.");
    }
}
