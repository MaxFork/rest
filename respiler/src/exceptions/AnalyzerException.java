package exceptions;

import types.ErrorType;

public class AnalyzerException extends Exception 
{
	private static final long serialVersionUID = 2340617995572042501L;
	
	public ErrorType type;
	
	int startLine;
	int startIndex;
	
	int endLine;
	int endIndex;
	
	public AnalyzerException(ErrorType type, int startLine, int startIndex, int endLine, int endIndex)
	{
		this.type = type;
		this.startLine = startLine;
		this.startIndex = startIndex;
		this.endLine = endLine;
		this.endIndex = endIndex;
	}
}
