public class TimePeriods{
	public String daysToPeriod(int days){
		if(days == 365){
			return "year";
		}
		else if(days == 31){
			return "month";
		}
		else if(days == 1){
			return "day";
		}
		else if(days == 7){
			return "week";
		}
		else if(days == 3652){
			return "decade";
		}
		else{
			return "no match";
		}
	}
	
	public int periodToDays(String period){
		String compStr = period.toLowerCase();
		if(compStr.equals("day")){
			return 1;
		}
		else if(compStr.equals("month")){
			return 31;
		}
		else if(compStr.equals("year")){
			return 365;
		}
		else if(compStr.equals("decade")){
			return 3652;
		}
		else if(compStr.equals("week")){
			return 7;
		}
		else{
			return -1;
		}
	}

	public static void main(String[] args){
		TimePeriods t = new TimePeriods();
		System.out.println(t.daysToPeriod(365));
		System.out.println(t.daysToPeriod(999));
		System.out.println(t.daysToPeriod(31));
		System.out.println(t.daysToPeriod(30));
	}
}
