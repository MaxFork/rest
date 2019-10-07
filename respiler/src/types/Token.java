package types;

public class Token 
{
	public TokenType type;
	
	public int startLine;
	public int endLine;
	
	public int startIndex;
	public int endIndex;
	
	public Token(TokenType type, int startLine, int endLine, int startIndex, int endIndex)
	{
		this.type = type;
		
		this.startLine = startLine;
		this.endLine = endLine;
		
		this.startIndex = startIndex;
		this.endIndex = endIndex;
	}
}
