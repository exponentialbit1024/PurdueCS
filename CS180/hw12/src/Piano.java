/**
 * Created by sidshah on 4/21/17.
 */
public class Piano extends StringInstrument {
    private String key;
    public Piano(String musicianName, int numStrings, String key){
        super(musicianName, numStrings);
        this.key = key;
    }
    public String getKey(){
        return this.key;
    }
    public void play(String song){
        System.out.println(super.getMusicianName() + " is playing " + song + " on a " + super.getNumStrings() + " string piano in the key of " + getKey());
    }
}
