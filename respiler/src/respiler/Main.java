package respiler;

import java.io.IOException;

import exceptions.BaseException;
import types.Line;

public class Main 
{
	public static final boolean SAFE = true;
	
	public static void main(String[] args) throws IOException, BaseException
	{
		byte[] buffer;
		Line[] lines;
		
		buffer = Respiler.readFile("code.rest");
		Respiler.splitLines(buffer);
	}
}
