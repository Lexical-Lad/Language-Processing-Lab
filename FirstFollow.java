import java.io.*;
import java.util.*;

class FirstFollow
{

	static char availVariable(LinkedList variables)
	{
		for(int i=65;i<=90;i++)
		{
			if(variables.indexOf((char)i)==-1)
			return (char)i;
		}

		return 0;
	}

	static void lambda(String p,LinkedList productions)
	{
		if(p.charAt(0)=='~')
		{
			System.out.print("~");
			return;
		}
		if(p.length()==0)
		{
			System.out.print("~");
			return;
		}

		if(p.charAt(0)<65 || p.charAt(0)>90)
		return;

		if(productions.indexOf((Character.toString(p.charAt(0))) +"->~")!=-1)
		lambda(p.substring(1),productions);


	}


	static void first(String p,LinkedList productions)
	{

		if(p.charAt(0)=='~')
			return;

		if(p.charAt(0)<65 || p.charAt(0)>90)
		{
			System.out.print(p.charAt(0)+" ,");
			return;
		}
		else
		{
			int len=p.length();
			for(int j=0;j<len;j++)
			{
				for(int i=0;i<productions.size();i++)
				{
					String pp=(String)productions.get(i);

					if(pp.charAt(0)==p.charAt(0))
					first(pp.substring(pp.indexOf("->")+2),productions);

				}
				p=p.substring(1);
			}

		}
		return;


	}

	static void firstF(String p,LinkedList productions,String s[],int n)
		{

			if(p.charAt(0)=='~')
			return;

			if(p.charAt(0)<65 || p.charAt(0)>90)
			{
				if(s[n].indexOf(p.charAt(0))==-1)
				s[n]+=p.charAt(0);
				return;
			}
			else
			{
				int len=p.length();
				for(int j=0;j<len;j++)
				{
					for(int i=0;i<productions.size();i++)
					{
						String pp=(String)productions.get(i);

						if(pp.charAt(0)==p.charAt(0))
						firstF(pp.substring(pp.indexOf("->")+2),productions,s,n);

					}
					p=p.substring(1);
				}

			}
			return;


	}


	public static void main(String args[])throws IOException

	{
		BufferedReader xx=new BufferedReader (new InputStreamReader(System.in));

		System.out.println("Enter all the productions using '->' sign as usual. Enter '_|_' to stop : (assume ~ to be lambda). \nAlso, enter all productions as separate lines(i.e if S->a/b, then drop the smartassery and wrtie 'S->a' and 'S->b')");

		LinkedList productions=new LinkedList();
		LinkedList terminals=new LinkedList();
		LinkedList variables=new LinkedList();


		String temp;

		while(!(temp=xx.readLine()).equals("_|_"))
		{

			productions.add(temp);
			int num=temp.length();
			char c=temp.charAt(0);

			if(variables.indexOf(Character.toString(c))==-1)
			variables.add(Character.toString(c));

			for(int i=3;i<num;i++)
			{
				c=temp.charAt(i);

				if(c>=65 && c<=90)
				{
					//System.out.println(c);
					if(variables.indexOf(Character.toString(c))==-1)
					variables.add(Character.toString(temp.charAt(i)));
				}
				else
				{
					if(terminals.indexOf(c)==-1)
					terminals.add(temp.charAt(i));
				}
			}

		}

		System.out.println(Arrays.toString(productions.toArray()));
		System.out.println(Arrays.toString(variables.toArray()));
		System.out.println(Arrays.toString(terminals.toArray()));



		//removing left recursion

		int num=productions.size();

		for(int i=0;i<num;i++)
		{
			String p=(String)productions.get(i);
			char c=p.charAt(0);

			if(c==p.charAt(p.indexOf("->")+2)) //left recursion detected
			{
				i=-1;
				char cc=availVariable(variables);

				variables.add(Character.toString(cc));
				productions.add(Character.toString(cc)+"->~");
				num++;

				for(int j=0;j<num;j++)
				{
					//System.out.print(j);
					String pp=(String)productions.get(j);
					//System.out.println("\t"+pp);

					if(pp.substring(0,pp.indexOf("->")).equals(Character.toString(c)))
					{


						if(pp.charAt(pp.indexOf("->")+2)==c)
						{

							productions.remove(j);j--;
							productions.add(cc+"->"+ pp.substring(pp.indexOf("->")+3)+cc);
						}
						else if(pp.charAt(pp.indexOf("->")+2)!='~' && pp.charAt(pp.length()-1)!=cc)
						{
							productions.remove(j);j--;
							productions.add(c+"->"+pp.substring(pp.indexOf("->")+2)+cc);
						}


					}

				}

			}
		}

				System.out.println(Arrays.toString(productions.toArray()));
				System.out.println(Arrays.toString(variables.toArray()));
				System.out.println(Arrays.toString(terminals.toArray()));



			//Left recursion removed

			//finding firsts

			 num=variables.size();

			for(int i=0;i<num;i++)
			{
				char c=((String)variables.get(i)).charAt(0);


				System.out.print("First("+c+") : \t");



				for(int j=0;j<productions.size();j++)
				{

					String pp=(String)productions.get(j);



					if(pp.charAt(0)==c)
					first(pp.substring(pp.indexOf("->")+2),productions);

					if(pp.charAt(0)==c)
					lambda(pp.substring(pp.indexOf("->")+2),productions);

				}


				System.out.println();


			}

			//finding follows

			String follow[]=new String[variables.size()];

			Arrays.fill(follow,"");

			follow[variables.indexOf("S")]+="$";

			for(int i=0;i<num;i++)
			{
				char c=((String)variables.get(i)).charAt(0);


				for(int j=0;j<productions.size();j++)
				{
					String p=(String)productions.get(j);
					p=p.substring(p.indexOf("->")+2);

					if(p.indexOf(Character.toString(c))!=-1 && p.indexOf(Character.toString(c))!=(p.length()-1))
					firstF(p.substring(p.indexOf(Character.toString(c))+1),productions,follow,variables.indexOf(Character.toString(c)));


				}

			}

			for(int i=0;i<num;i++)
			{
				char c=((String)variables.get(i)).charAt(0);


				for(int j=0;j<productions.size();j++)
				{
					String p=(String)productions.get(j);
					String pp=p.substring(p.indexOf("->")+2);

					if(pp.indexOf(Character.toString(c))==(pp.length()-1))
					{
						for(int k=0;k<follow[variables.indexOf((Character.toString(p.charAt(0))))].length();k++)
						if(follow[variables.indexOf(Character.toString(c))].indexOf(follow[variables.indexOf((Character.toString(p.charAt(0))))].charAt(k))==-1)
						follow[variables.indexOf(Character.toString(c))]+=follow[variables.indexOf((Character.toString(p.charAt(0))))].charAt(k);
					}


				}

				System.out.println("Follow("+c+"):\t"+follow[variables.indexOf(Character.toString(c))]);

			}







	}

}

