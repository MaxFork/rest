package respiler;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import exceptions.BaseException;
import exceptions.BigFileSizeException;
import exceptions.ReadNumberException;
import types.BufferLines;
import types.ByteTest;
import types.Line;
import types.Token;
import types.TokenStream;

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
			result[lnum] = new Line(0, 0);
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
				
				lnum += 1;
				result[lnum].start = index;
				
			}
			else if (array[index] == '\n')
			{
				index += 1;
				
				result[lnum].end = index;
				
				if (index == array.length)
					break;
				
				lnum += 1;
				result[lnum].start = index;
			}
			else
			{
				index += 1;
				
				if (index == array.length)
				{
					result[lnum].end = index;
					break;
				}
			}
		}
		
		return result;
	}
	
	public static BufferLines readLines(FileInputStream stream) throws IOException, BaseException
	{
		BufferLines bufferLines = new BufferLines();
		
		bufferLines.buffer = readFile(stream);
		bufferLines.lines = splitLines(bufferLines.buffer);
		return bufferLines;
	}
	
	public static TokenStream analyzeBufferLines(BufferLines _bufferLines)
	{
		return new TokenStream() 
		{
			private BufferLines bufferLines;
			private int lnum;
			private int index;
			private boolean end;
			
			{
				this.bufferLines = _bufferLines;
				this.lnum = 0;
				this.index = bufferLines.lines[lnum].start;
				this.end = false;
			}
			
			private void incIndex()
			{
				index += 1;
				if (index == bufferLines.lines[lnum].end)
				{
					lnum += 1;
					if (lnum == bufferLines.lines.length)
					{
						lnum -= 1;
						end = true;
						return;
					}
					index = bufferLines.lines[lnum].start;
				}
			}
			
			private byte byteAtIndex()
			{
				return bufferLines.buffer[index];
			}
			
			@Override
			public Token nextToken() 
			{
				while (ByteTest.isBlank.test(byteAtIndex()))
				{
					incIndex();
					if (end)
						return null;
				}
				
				if (ByteTest.isLower.test(byteAtIndex()))
				{
					
				}
				return null;
			}
		};
	}
}
