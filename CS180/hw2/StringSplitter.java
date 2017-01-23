public class StringSplitter {
  public String formSubmission(String s){
    String[] parts = s.split("\\s+|,\\s*|\\.\\s*");
    String fName = parts[0];
    String lName = parts[1];
    String dob = parts[2];
    int bYear = Integer.parseInt(parts[2].split("/")[2]);
    int appAge = 2017 - bYear;
    String retString = "First Name: " + fName + "\n" + "Last Name: " + lName + "\n" + "Approximate Age: " + String.valueOf(appAge);
    return retString;
  }

  public static void main(String[] args){
    StringSplitter usageObject = new StringSplitter();
    String inputString = "John Doe, 12/7/1992";
    String formString = usageObject.formSubmission(inputString);
    System.out.println(formString);
  }
}
