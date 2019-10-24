package types;

import exceptions.AnalyzerException;

public interface TokenStream 
{
	public Token nextToken() throws AnalyzerException;
}
