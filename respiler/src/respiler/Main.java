package respiler;

import java.io.IOException;

import exceptions.BaseException;
import types.ByteTest;
import types.Line;

public class Main 
{
	public static final boolean SAFE = true;
	
	public static void main(String[] args) throws IOException, BaseException
	{
		byte[] buffer;
		Line[] lines;
		Line line;
		
		buffer = Respiler.readFile("code.rest");
		lines = Respiler.splitLines(buffer);
		line = new Line();
		
		for (int i = 0; i < lines.length; i += 1)
		{
		}
	}
}
