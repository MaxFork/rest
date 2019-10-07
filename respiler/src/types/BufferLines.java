package types;

public class BufferLines 
{
	public byte[] buffer;
	public Line[] lines;
	
	public BufferLines(byte[] buffer, Line[] lines)
	{
		this.buffer = buffer;
		this.lines = lines;
	}
	
	public BufferLines()
	{
		this.buffer = null;
		this.lines = null;
	}
}
