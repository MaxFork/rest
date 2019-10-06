package respiler;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import exceptions.BaseException;
import exceptions.BigFileSizeException;
import exceptions.ReadNumberException;
import types.Line;

public class Respiler 
{	
	public static byte[] readFile(FileInputStream stream) throws IOException, BaseException
	{
		long fileSize;
		int readNumber;
		byte[] array;
		
		fileSize = stream.getChannel().size();
		if (fileSize > Integer.MAX_VALUE)
		{
			throw new BigFileSizeException("file size: " + fileSize);
		}
		
		array = new byte[(int)fileSize];
		
		readNumber = stream.read(array);
		if (readNumber != fileSize)
		{
			throw new ReadNumberException("read number: " + readNumber + ", file size: " + fileSize);
		}
		return array;
	}
	
	public static byte[] readFile(String name) throws FileNotFoundException, IOException, BaseException
	{
		return readFile(new FileInputStream(name));
	}
	
	public static Line[] splitLines(byte[] array)
	{
		Line[] result;
		int total;
		int index;
		int lnum;
		
		index = 0;
		total = 0;
		while (true)
		{
			if (array[index] == '\r')
			{
				total += 1;
				
				index += 1;
				if (index == array.length)
					break;
				
				if (array[index] == '\n')
				{
					index += 1;
					
					if (index == array.length)
						break;
				}
			}
			else if (array[index] == '\n')
			{
				total += 1;
				
				index += 1;
				if (index == array.length)
					break;
			}
			else
			{
				index += 1;
				if (index == array.length)
				{
					total += 1;
					break;
				}
			}
		}
		
		result = new Line[total];
		for (lnum = 0; lnum < result.length; lnum += 1)
		{
			result[lnum] = new Line(array, 0, 0);
		}
		
		index = 0;
		lnum = 0;
		
		result[lnum].start = index;
		while (true)
		{
			if (array[index] == '\r')
			{
				index += 1;
				
				array[index] = '\n';
				result[lnum].end = index;
				
				if (index == array.length)
					break;
				
				if (array[index] == '\n')
				{
					index += 1;
					
					if (index == array.length)
						break;
				}
				
			}
			else if (array[index] == '\n')
			{
				index += 1;
				
				result[lnum].end = index;
				
				if (index == array.length)
					break;
				
				lnum += 1;
			}
			else
			{
				
			}
		}
	}
}
