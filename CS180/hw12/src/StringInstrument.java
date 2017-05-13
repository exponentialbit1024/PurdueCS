/**
 * Created by sidshah on 4/21/17.
 */
public abstract class StringInstrument extends Instrument{
    private int numStrings;
    public StringInstrument(String musicianName, int numStrings){
        super(musicianName);
        this.numStrings = numStrings;
    }
    public int getNumStrings(){
        return this.numStrings;
    }
}
