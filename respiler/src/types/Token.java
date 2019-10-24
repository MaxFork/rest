package types;

public class Token 
{
	public TokenType type;
	
	public int startLine;
	public int startIndex;
	
	public int endLine;
	public int endIndex;
	
	public Token(TokenType type, int startLine, int startIndex, int endLine, int endIndex)
	{
		this.type = type;
		
		this.startLine = startLine;
		this.endLine = endLine;
		
		this.startIndex = startIndex;
		this.endIndex = endIndex;
	}
}
