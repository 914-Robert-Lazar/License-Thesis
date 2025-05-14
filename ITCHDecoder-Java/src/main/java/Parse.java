import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.zip.GZIPInputStream;

/**
 * Parse will take an ITCH 4.1 binary file as input, read that file as byte arrays
 * Then, if the user wants, parse the message to human-readable format via the Parsers and print
 * Finally, it will return the message as a byte array
 *
 * @author William Sell
 *
 * quannabe@gmail.com
 *
 */


public class Parse {

    private String filename;

    // This is the yaml file where the
    private String yamlFile = "C:\\Programs\\Informatics-University-Projects\\Informatics University\\License Thesis\\License-Thesis\\ITCHDecoder-Java\\src\\main\\resources\\itch41.yaml";

    private boolean print;

    private byte[] lenBytes = new byte[2];

    private InputStream input;

    Parsers parsers;
    ParseDS parseDS;

    public int orderRelatedMessageCounter = 0;

    private List<String> orderRelatedMessageType = Arrays.asList("A", "F", "E", "C", "X", "D", "U");

    // Constructor with the ITCH5.0 binary file location as arg
    public Parse(String filename, boolean print) {

        // Check arg for printing parsing the message
        this.print = print;

        // Via YAML, create the Data Structures
        try {
            parseDS = new ParseDS(yamlFile);
        } catch (FileNotFoundException e) {
            System.out.println("File not found...Check Filename");
            e.printStackTrace();
        }

        // Create the parsers with the YAML data structures
        parsers = new Parsers(parseDS);
        this.filename = filename;

        // Open the data file
        try {
            InputStream fileInputStream = new FileInputStream(new File(filename));
            input = new GZIPInputStream(fileInputStream);
        } catch (IOException e) {
            System.out.println("File not found...Check Filename");
            e.printStackTrace();
        }
    }

    public static int readFully(InputStream in, byte[] buffer) throws IOException {
        int totalRead = 0;
        while (totalRead < buffer.length) {
            int bytesRead = in.read(buffer, totalRead, buffer.length - totalRead);
            if (bytesRead == -1) {
                break;
            }
            totalRead += bytesRead;
        }
        return totalRead;
    }

    // Read the message from binary file
    public byte[] parse() throws IOException, InterruptedException{

        // EOF conditions
        if (input.read() == -1){
            return null;
        }

        int payLength = input.read();

        // Get the payload
        byte[] payBytes = new byte[payLength];
        int numberOfBytesRead = readFully(input, payBytes);

        ArrayList<String> messageArr = null;

        // Send payBytes byte[] to Parsers for processing
        // An arraylist will be returned with the message
        messageArr = (parsers.messageIn(payBytes));
        if (orderRelatedMessageType.contains(messageArr.get(0))) {
            orderRelatedMessageCounter++;
        }
        // Check if we are parsing and printing
        if (print){
            System.out.println( messageArr);
        }
        return payBytes;
    }

    // Main test harness
    public static void main(String[] args) throws IOException, InterruptedException {
        // ITCH file location
        if (args.length < 2) {
            System.out.println("Usage: java -jar <Selected JAR file> <parse or build> <binary_itch_file.gz> [<number of order related messages to be executed>]");
            return;
        }

        String filename = args[1];

        int orderRelatedMessagesToExecuted = 0;
        if (args.length > 2) {
            orderRelatedMessagesToExecuted = Integer.parseInt(args[2]);
        }
        // Set this to 'false' to supress output
        boolean PP = false;

        Parse parse = new Parse(filename, PP);

        int count = 0;

        final long startTime = System.currentTimeMillis();

        while ((orderRelatedMessagesToExecuted == 0 || parse.orderRelatedMessageCounter < orderRelatedMessagesToExecuted) && parse.parse() != null){

        }
        final long endTime = System.currentTimeMillis();

        System.out.println((endTime - startTime)* 0.001);
//        System.out.println("Messages/second: " + count/((endTime - startTime)* 0.001) );
    }
}
