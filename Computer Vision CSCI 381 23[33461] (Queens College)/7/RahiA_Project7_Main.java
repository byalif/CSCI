package RahiA_Project7;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;


public class RahiA_Project7_Main {
	static class Point{
		int row=-1, col=-1;
		public Point() {}
		public Point(int row, int col) {
			this.row = row;
			this.col = col;
		}
		
	}
	static class CCProperty{
		int label=-1, numPixels=-1, minRow=-1, minCol=-1, maxRow=-1, maxCol=-1;
		public CCProperty() {}
	}
	static Scanner inFile, prop, chainCodeScan;
	static BufferedWriter prettyPrintFile, chainCodeFile, BoundaryFile;
	static BufferedWriter debugFile;
	
	static class ChainCode{
		Point point;
		CCProperty CC;
	    int numRows, numCols, minVal, maxVal, numCC;
	    int[][] imgAry, boundaryAry, CCAry;
	    Point[] coordOffset = new Point[8];
	    int[] zeroTable = {6, 0, 0, 2, 2, 4, 4, 6};
		Point startP, currentP ,nextP;
		int lastQ, nextDir, PchainDir;
	    
	    
	    public ChainCode(int numImgRows, int numImgCols,int imgMin,int imgMax) throws IOException{
			this.numRows = numImgRows;
			this.numCols = numImgCols;
			this.minVal = imgMin;
			this.maxVal = imgMax;
			imgAry = new int[numImgRows+2][numImgCols+2];
			boundaryAry = new int[numImgRows+2][numImgCols+2];
			CCAry = new int[numImgRows+2][numImgCols+2];
			coordOffset[0] = new Point(0,1);
			coordOffset[1] = new Point(-1,1);
			coordOffset[2] = new Point(-1,0);
			coordOffset[3] = new Point(-1,-1);
			coordOffset[4] = new Point(0,-1);
			coordOffset[5] = new Point(1,-1);
			coordOffset[6] = new Point(1,0);
			coordOffset[7] = new Point(1,1);
			
			CC= new CCProperty();
			startP = new Point();
			nextP = new Point(); 
			currentP = new Point(); 
			
	        zero2DAry(imgAry);  
	        zero2DAry(boundaryAry); 
	    }



	    void loadImage(){
	        for(int i =1; i<=numRows; i++){
	            for(int j=1; j<=numCols; j++){
	                imgAry[i][j] = inFile.nextInt();
	            }
	        }

	    }
	    

	    void zero2DAry(int[][] ary){
	        for(int i =0; i<ary.length; i++){
	            for(int j=0; j<ary[i].length; j++){
	                ary[i][j] = 0;
	            }
	        }
	    }
	    
	    void loadCCAry(int CClabel, int[][] CCAry) {
	        for(int i =0; i<CCAry.length; i++){
	            for(int j=0; j<CCAry[i].length; j++){
	                if(imgAry[i][j]==CClabel) {
	                	CCAry[i][j] = CClabel;
	                }
	            }
	        }
	    }



	    
		public void reformatPrettyPrint(BufferedWriter file, int[][] ary) throws IOException {
	        for(int i=0; i<=numRows+1; i++){
	        	file.write("\n");
	            for(int j=0; j<=numCols+1; j++){
	                if(i< ary.length && j < ary[i].length && ary[i][j] > 0 ) file.write(ary[i][j]+" ");
	                else file.write("  ");
	            }
	        }
		}
		
		   
	    void prettyPrint(int[][] ary) throws IOException{
	        for(int i =1; i<=numRows; i++){
	            if(i>1) prettyPrintFile.write("\n");
	            for(int j=1; j<=numCols; j++){
	                if(ary[i][j] > 0){
	                    if (ary[i][j] < 10){ 
	                    	prettyPrintFile.write(ary[i][j]+"  ");
	                    }
	                    else if(ary[i][j] < 100){   
	                    	prettyPrintFile.write(ary[i][j]+ " ");
	                    }
	                    else{  
	                    	prettyPrintFile.write(ary[i][j]+ ary[i][j]);
	                    }
	                }
	                else prettyPrintFile.write("  .  ");

	            }
	        }

	    }
	    
	    int mod(int n, int mod){
	        int temp = n;
	        while(temp < 0){
	            temp += mod;
	        }
	        return temp%mod;
	    }

	    public int findNextP(int lastQ) throws IOException {
	    	debugFile.write("entering findNextP method\n");
	    	
	    	//last zero
	    	int index = lastQ;
	    	int i, j;
	    	boolean found = false;
	    	int ans =-1;
	    	
	    	while(!found){
		    	i = currentP.row + coordOffset[index].row;
		    	j = currentP.col +  coordOffset[index].col;

		    	if(imgAry[i][j] == CC.label) {
			    	debugFile.write("leaving findNextP method\nchainDir = " + index+"\n");
		    		found = true;
		    		return index;
		    	}
		    	else {
		    	index = mod(++index, 8);
		    	}
		    	
	    	}
	    	
	    	return ans;
	    }
	    

		public void getChainCode(CCProperty cc, int[][] ary, BufferedWriter chainCodeFile) throws IOException {
			debugFile.write("entering chainCode method\n");

			boolean found = false;
			
		    for(int i=1; i<=numRows; i++){
		    	if(found) break;
	            for(int j=1; j<=numCols; j++){
	                if (CCAry[i][j] == CC.label){
	                	chainCodeFile.write(CC.label+" "+i+" "+j+" ");
	                    startP.row = i;
	                    startP.col = j;
	        			currentP.row = i;
	        			currentP.col = j;
	        			lastQ = 4;
	        			found = true;
	        			break;
	                }
	            }
		    }
		       
			
			do {					
				int nextQ = mod(++lastQ, 8);
				PchainDir = findNextP(nextQ);
				
				if(PchainDir <0) break;
				chainCodeFile.write(PchainDir+" ");
				nextP.row = currentP.row + coordOffset[PchainDir].row;
				nextP.col = currentP.col +coordOffset[PchainDir].col;
				currentP = nextP;
				if(PchainDir == 0) {
					lastQ = zeroTable[7];
				}
				else {
					lastQ = zeroTable[PchainDir-1];
				}
				debugFile.write("lastQ = "+ lastQ +" nextQ = "+nextQ +" ; currentP.row = "+ currentP.row +" ; currentP.col = "+ currentP.col+" : nextP.row = "+ nextP.row+" : nextP.col = "+nextP.col+"\n");
			}while(currentP.row != startP.row || currentP.col != startP.col);
			
			debugFile.write("Leaving getChain method \n");

		}



	    public void pretty(int[][] ary) throws IOException{
	        for(int i =1; i<=numRows; i++){
	            if(i>1) BoundaryFile.write("\n");
	            for(int j=1; j<=numCols; j++){
	                if(ary[i][j] > 0){
	                    if (ary[i][j] < 10){ 
	                        BoundaryFile.write(ary[i][j]+"  ");
	                    }
	                    else if(ary[i][j] < 100){   
	                    	BoundaryFile.write(ary[i][j]+ " ");
	                    }
	                    else{  
	                    	BoundaryFile.write(ary[i][j]+ ary[i][j]);
	                    }
	                }
	                else BoundaryFile.write("  .  ");

	            }
	        }
	    }


		public void goToNext(int next) {
	        switch(next){
            case 0:
                currentP.row = currentP.row;
                currentP.col = currentP.col+1;
                break;
            case 1:
            	currentP.row = currentP.row-1;
            	currentP.col = currentP.col+1;
                break; 
            case 2:
            	currentP.row = currentP.row-1;
            	currentP.col = currentP.col;
                break;
            case 3:
            	currentP.row = currentP.row-1;
            	currentP.col = currentP.col-1;
                break;
            case 4:
            	currentP.row = currentP.row;
            	currentP.col = currentP.col-1;
                break;
            case 5:
            	currentP.row = currentP.row+1;
                currentP.col = currentP.col-1;
                break; 
            case 6:
            	currentP.row = currentP.row+1;
            	currentP.col = currentP.col;
                break;
            case 7:
            	currentP.row = currentP.row+1;
                currentP.col = currentP.col+1;
                break;  
        }
			
		}


	}
	

	private static boolean checkBoundary(int row, int col, int[][] ary) {
		return row>=0 && col>=0 && row<= ary.length && col<= ary[row].length;
	}

	
	
    public static void main(String[] args) throws IOException{
    	//Step 0
		File labelFile = new File(args[0]+".txt");
		File propFile = new File(args[1]+".txt");
		File outFile = new File(args[2]+".txt");
		prettyPrintFile = new BufferedWriter(new FileWriter(outFile));
		File debug = new File("debugFile.txt");
		debugFile = new BufferedWriter(new FileWriter(debug));
		
		int numImgRows, numImgCols,imgMin,imgMax;
    	inFile = new Scanner(labelFile);
    	prop = new Scanner(propFile);
		numImgRows = inFile.nextInt();
		numImgCols = inFile.nextInt();
		imgMin = inFile.nextInt();
		imgMax = inFile.nextInt();
		
		ChainCode chainCode = new ChainCode(numImgRows,numImgCols,imgMin,imgMax);
		
		numImgRows = prop.nextInt(); 
		numImgCols = prop.nextInt();
		imgMin = prop.nextInt();
		imgMax = prop.nextInt();
		chainCode.numCC = prop.nextInt();
		
		//Repeat steps 2-5
		
		//Step 1
		File chainCodeFileName = new File(args[1]+ "_chainCode.txt");
		File BoundaryFileName = new File(args[1]+ "_Boundary.txt");

		 if(chainCodeFileName.createNewFile()){
	            System.out.println(args[1]+ "_chainCode.txt"+" File Created");
	        }else System.out.println("File "+args[1]+ "_chainCode.txt"+" already exists");
	        
		 if(BoundaryFileName.createNewFile()){
	            System.out.println(args[1]+ "_Boundary.txt"+" File Created");
	        }else System.out.println("File "+args[1]+ "_Boundary.txt"+" already exists");
		 
		 chainCodeFile = new BufferedWriter(new FileWriter(chainCodeFileName));
		 BoundaryFile =  new BufferedWriter(new FileWriter(BoundaryFileName));
		 
		 chainCodeFile.write(numImgRows+" "+numImgCols+" "+ imgMin+" "+imgMax+"\n"+chainCode.numCC+"\n");
		 
		 int tmp = chainCode.numCC;
		
		while(tmp >  0) {
			tmp--;
			
			chainCode.loadImage();
			
			chainCode.reformatPrettyPrint(prettyPrintFile, chainCode.imgAry);
			prettyPrintFile.write("\n");
			
			 
			 //Step 2
			 
			 chainCode.CC.label = prop.nextInt();
			 chainCode.CC.numPixels = prop.nextInt();
			 chainCode.CC.minRow = prop.nextInt();
			 chainCode.CC.minCol = prop.nextInt();
			 chainCode.CC.maxRow = prop.nextInt();
			 chainCode.CC.maxCol = prop.nextInt();
			 
			 chainCode.zero2DAry(chainCode.CCAry);
			 chainCode.loadCCAry(chainCode.CC.label, chainCode.CCAry);
			 chainCode.reformatPrettyPrint(prettyPrintFile, chainCode.CCAry);
			 
			 chainCode.getChainCode(chainCode.CC, chainCode.CCAry, chainCodeFile); 
		        
		}
		
		chainCodeFile.close();
		
		
		tmp = chainCode.numCC;
		File openChainCode = new File(args[1]+"_chainCode.txt");
		chainCodeScan = new Scanner(openChainCode);
		
		while(chainCodeScan.hasNext()) {

			numImgRows = chainCodeScan.nextInt();
			numImgCols = chainCodeScan.nextInt();
			imgMin = chainCodeScan.nextInt();
			imgMax = chainCodeScan.nextInt();   
			
	        chainCode.numCC =  chainCodeScan.nextInt(); 
	        chainCode.CC.label =  chainCodeScan.nextInt();   
	        chainCode.currentP.row = chainCodeScan.nextInt();
	        chainCode.currentP.col = chainCodeScan.nextInt();
			
	        int next;
	        
	        while(chainCodeScan.hasNext() && checkBoundary(chainCode.currentP.row, chainCode.currentP.col, chainCode.boundaryAry)){
	        	chainCode.boundaryAry[chainCode.currentP.row][chainCode.currentP.col] = chainCode.CC.label;
	            next = chainCodeScan.nextInt();
	            chainCode.goToNext(next);
	        }
	        //write to boundaryFile
	        chainCode.pretty(chainCode.boundaryAry);
	        

		}

		
		//important
		prettyPrintFile.close();
		prop.close();
		inFile.close();
		chainCodeFile.close();
		BoundaryFile.close();
		debugFile.close();
    }

}
