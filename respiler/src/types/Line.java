package types;

public class Line 
{
	public byte[] buffer;
	public int start;
	public int end;
	
	public Line(byte[] buffer, int start, int end)
	{
		this.buffer = buffer;
		this.start = start;
		this.end = end;
	}
	
	public Line()
	{
		this(null, 0, 0);
	}
}
