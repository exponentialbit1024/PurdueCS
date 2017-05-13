/**
 * Created by sidshah on 4/21/17.
 */
public abstract class WoodwindInstrument extends Instrument{
    private WoodwindType type;
    public WoodwindInstrument(String musicianName, WoodwindType type){
        super(musicianName);
        this.type = type;
    }

    public String getType(){
        return this.type.toString();
    }
}
