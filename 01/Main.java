import java.io.*;

class Main {

  public static String read_file(String path) throws IOException {
    BufferedReader reader = new BufferedReader(new FileReader(path));
    String content = reader.readLine();
    reader.close();
    return content;
  }

  public static void main(String[] args) throws IOException {
    String line = read_file("input.txt");

    int floor = 0;
    int count_down = 0;
    int count_up = 0;
    Object[] entered = {0, false};
    for (int i = 0; i < line.length(); i++) {
      if (line.charAt(i) == '(') {
        floor += 1;
        count_up += 1;
      } else if (line.charAt(i) == ')') {
        if (floor == 0 && (Boolean) entered[1] == false) {
          entered[0] = i + 1;
          entered[1] = true;
        }
        count_down += 1;
        floor -= 1;
      }
    }
    System.out.println("Floor: " + floor);
    System.out.println("Entered basement at: " + entered[0]);
  }
}
