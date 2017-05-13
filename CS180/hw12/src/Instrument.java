/**
 * Created by sidshah on 4/21/17.
 */
public abstract class Instrument {
    private String musicianName;

    public Instrument(String musicianName){
        this.musicianName = musicianName;
    }

    public String getMusicianName(){
        return this.musicianName;
    }

    public abstract void play(String song);
}
