package types;

public interface ByteTest 
{
	public boolean test(byte b);
	
	public static ByteTest isBlank = new ByteTest() 
	{
		@Override
		public boolean test(byte b) 
		{
			return (b == ' ') || (b == '\t');
		}
	};
	
	public static ByteTest isLower = new ByteTest()
	{
		@Override
		public boolean test(byte b) 
		{
			return ('a' <= b) && (b <= 'z');
		} 
	};
	
	public static ByteTest isUpper = new ByteTest()
	{
		@Override
		public boolean test(byte b) 
		{
			return ('A' <= b) && (b <= 'Z');
		} 
	};
	
	public static ByteTest isDigit = new ByteTest()
	{
		@Override
		public boolean test(byte b) 
		{
			return ('0' <= b) && (b <= '9');
		} 
	};
	
	public static ByteTest isLetter = new ByteTest()
	{
		@Override
		public boolean test(byte b) 
		{
			return  (('a' <= b) && (b <= 'z')) || 
					(('A' <= b) && (b <= 'Z'));
		} 
	};
	
	public static ByteTest isHexDigit = new ByteTest()
	{
		@Override
		public boolean test(byte b) 
		{
			return  (('0' <= b) && (b <= '9')) || 
					(('a' <= b) && (b <= 'f')) ||
					(('A' <= b) && (b <= 'F'));
		} 
	};
}
