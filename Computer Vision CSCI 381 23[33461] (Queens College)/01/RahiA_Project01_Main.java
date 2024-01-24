package RahiA_Project0;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class RahiA_Project01_Main {
	public static void main(String[] args) {
		if (2 <= args.length) {
			File inFile = new File(args[0]);
			File outFile = new File(args[1]);
    		processing(inFile, outFile, 6);
	        
		} else {
		   System.err.println("Invalid arguments count:" + args.length);
		   System.exit(0);
		}
		
	}
	

	private static void processing(File inFile, File outFile, int thrVal) {
		BufferedWriter bw = null;
		Scanner scanner;
		try {
			bw = new BufferedWriter(new FileWriter(outFile));
			
			try {
				scanner = new Scanner(inFile);
				int row;
				int col;
				int low;;
				int high;
				
				row = scanner.nextInt();
				col = scanner.nextInt();
				low = scanner.nextInt();
				high = scanner.nextInt();
				//write the header
				bw.write(row+" "+col+" "+low+" "+high+"\n");
				
				for(int i=0; i<row; i++) {
					for(int j=0; j<col; j++) {
						if(scanner.hasNextInt()){
							if(scanner.nextInt() >= thrVal) {
								//write 1 to output.txt
								bw.write(1+" ");
					        }
					        else {
					            //write 2 to output.txt
					            bw.write(0+" ");
					        }
								
						}
						else {
							scanner.next();
						}
					}
					bw.write("\n");
				}
				bw.close();
			
			} catch (FileNotFoundException e1) {
				System.out.println("oops. scanner error");
				e1.printStackTrace();
			}
		} catch (IOException e) {
			System.out.println("oops. bw error");
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
	}

	
	
	
}
