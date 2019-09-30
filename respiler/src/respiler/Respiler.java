package respiler;

import java.io.FileInputStream;
import java.io.IOException;

import exceptions.BaseException;
import exceptions.BigSizeException;
import exceptions.ReadNumberException;

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
			throw new BigSizeException("file size: " + fileSize);
		}
		
		array = new byte[(int)fileSize];
		
		readNumber = stream.read(array);
		if (readNumber != fileSize)
		{
			throw new ReadNumberException("read number: " + readNumber + ", file size: " + fileSize);
		}
		return array;
	}
	
}
