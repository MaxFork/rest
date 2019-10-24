package respiler;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.management.RuntimeErrorException;

import exceptions.AnalyzerException;
import exceptions.BaseException;
import exceptions.BigFileSizeException;
import exceptions.ReadNumberException;
import types.BufferLines;
import types.ByteTest;
import types.ErrorType;
import types.Line;
import types.Token;
import types.TokenStream;
import types.TokenType;

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
				array[index] = '\n';
				
				index += 1;
				
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
			private Token token;
			
			{
				this.bufferLines = _bufferLines;
				this.lnum = 0;
				this.index = bufferLines.lines[lnum].start;
				this.token = null;
				this.end = false;
				
			}
			
			private void setStartIndex()
			{
				token.startIndex = index;
				token.startLine = lnum;
			}
			
			private void setEndIndex()
			{
				token.endIndex = index;
				token.endLine = lnum;
			}
			
			private void setType(TokenType type)
			{
				token.type = type;
			}
			
			private AnalyzerException newException(ErrorType type)
			{
				return new AnalyzerException(type, token.startIndex, token.startLine, token.endLine, token.endIndex); 
			}
			
			private void setNameTypeCheckKeyword()
			{
				TokenType type;
				
				if (token.startLine == token.endLine)
				{
					type = Config.searchKeyword(bufferLines.buffer, token.startIndex, token.endIndex - token.startIndex);
					token.type = (type == null) ? TokenType.NAME : type;
				}
				throw new RuntimeException("write here!");
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
			
			private byte getByte()
			{
				return bufferLines.buffer[index];
			}
			
			@Override
			public Token nextToken() throws AnalyzerException 
			{
				token = new Token(null, 0, 0, 0, 0);
				
				if (end)
				{
					return null;
				}
				
				while (ByteTest.isBlank(getByte()))
				{
					incIndex();
					if (end)
						return null;
				}
				
				// newline
				
				if (getByte() == '\n')
				{
					setStartIndex();
					incIndex();
					setEndIndex();
					
					setType(TokenType.NEWLINE);
					return token;
				}
				
				// keyword or name
				
				else if (ByteTest.isLower(getByte()))
				{
					setStartIndex();
					
					incIndex();
					if (end)
					{
						setEndIndex();
						setNameTypeCheckKeyword();
						return token;
					}
					
					while (ByteTest.isLower(getByte()))
					{
						incIndex();
						if (end)
						{
							setEndIndex();
							setNameTypeCheckKeyword();
							return token;
						}
					}
					
					if (ByteTest.isUpper(getByte()) || ByteTest.isDigit(getByte()) || (getByte() == '_'))
					{
						incIndex();
						if (end)
						{
							setEndIndex();
							
							setType(TokenType.NAME);
							return token;
						}
						
						while (ByteTest.isLetter(getByte()) || ByteTest.isDigit(getByte()) || (getByte() == '_'))
						{
							incIndex();
							if (end)
								break;
						}
						
						setEndIndex();
						
						setType(TokenType.NAME);
						return token;
					}
					
					setEndIndex();
					
					setNameTypeCheckKeyword();
					return token;
				}
				
				// name
				
				else if (ByteTest.isUpper(getByte()) || (getByte() == '_'))
				{
					setStartIndex();
					
					incIndex();
					if (end)
					{
						setEndIndex();
						
						setType(TokenType.NAME);
						return token;
					}
					
					while (ByteTest.isLetter(getByte()) || ByteTest.isDigit(getByte()) || (getByte() == '_'))
					{
						incIndex();
						if (end)
							break;
					}
					
					setEndIndex();
					
					setType(TokenType.NAME);
					return token;
				}
				
				// number
				
				else if (ByteTest.isDigit(getByte()))
				{
					setStartIndex();
					
					incIndex();
					if (end)
					{
						setEndIndex();
						
						setType(TokenType.NUMBER);
						return token;
					}
					
					while (ByteTest.isDigit(getByte()))
					{
						incIndex();
						if (end)
						{
							break;
						}
					}
					
					setEndIndex();
					
					setType(TokenType.NUMBER);
					return token;
				}
				
				else if (getByte() == '.')
				{
					setStartIndex();
					incIndex();
					setEndIndex();
					
					setType(TokenType.DOT);
					return token;
				}
				
				// error
				
				else
				{
					setStartIndex();
					incIndex();
					setEndIndex();
					
					throw newException(ErrorType.INVALID_CHARACTER);
				}
			}
		};
	}
}
