package edu.qc.seclass;

import java.util.HashMap;
import java.util.Map;

public class MyCustomString implements MyCustomStringInterface {
	String str = null;
	Map<Integer, String> map = new HashMap();

	@Override
	public String getString() {
		return str;
	}

	@Override
	public void setString(String string) {
		str = string;
	}

	@Override
	public int countNumbers() {
		if(str == null) throw new NullPointerException();
		if(str.length() == 0) return 0;
		int i = 0;
		int count = 0;
		while(i < str.length()) {
			if(Character.isDigit(str.charAt(i))) {
				count++;
				while(i < str.length() && Character.isDigit(str.charAt(i))){
					i++;
				}
			}
			i++;
		}
		
		return count;
	}

	@Override
	public String getEveryNthCharacterFromBeginningOrEnd(int n, boolean startFromEnd) {
		if(n <= 0) throw new IllegalArgumentException();
		if(n > 0 && str == null) throw new NullPointerException();
		
		if(str.length() < n) return "";
		
		String tmp = str;
		String st = "";
		if(startFromEnd) {
			tmp = new StringBuilder(tmp).reverse().toString();
		}
		int i = n-1;
		while(i < tmp.length()) {
			st+= tmp.charAt(i);
			i+= n;
		}
		
		if(startFromEnd) {
			st = new StringBuilder(st).reverse().toString();
		}
		
		return st;
	}

	@Override
	public void convertDigitsToNamesInSubstring(int startPosition, int endPosition) {
		if(startPosition > endPosition) throw new IllegalArgumentException();
		if((startPosition <= endPosition) && (startPosition < 0 || endPosition >= str.length())) {
			throw new MyIndexOutOfBoundsException("Your indexes are invalid");
		}
		if(startPosition >= 0 && endPosition < str.length() && str == null) {
			throw new NullPointerException();
		}
		
		String tmp = "";
		map.put(0, "Zero");
		map.put(1, "One");
		map.put(2, "Two");
		map.put(3, "Three");
		map.put(4, "Four");
		map.put(5, "Five");
		map.put(6, "Six");
		map.put(7, "Seven");
		map.put(8, "Eight");
		map.put(9, "Nine");
		
		for(int i=0; i<startPosition-1; i++) {
			tmp+= str.charAt(i);
		}
		
		for(int i=startPosition-1; i<endPosition; i++) {
			if(map.containsKey(str.charAt(i) - '0')) {
				tmp+= map.get(str.charAt(i) - '0');
			}
			else {
				tmp+= str.charAt(i);
			}
		}
		
		for(int i=endPosition; i<str.length(); i++) {
			tmp+= str.charAt(i);
		}
		
		str = tmp;
	}

}
