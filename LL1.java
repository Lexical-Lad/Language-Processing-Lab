import java.io.*;
import java.util.*;

class LL1
{


	static void first(String p, LinkedList productions, String first[],String var) //first is a single element string array(used in place of a singular String variable as String objects are immutable, so in the pass-by-reference model, the changes aren't propagated upon concatenation)
																					//var is the variable whose first is being found
	{
		if(p.length()==0)return;
		if(p.charAt(0)==var.charAt(0))return; // to prevent infinite recursion

		if(p.charAt(0)=='~')
			return;


		if(p.charAt(0)<65 || p.charAt(0)>90)
		{
			if(first[0].indexOf(p.charAt(0))==-1)
			first[0]+=p.charAt(0);

			return;
		}

		boolean flag=false;

		for(int i=0;i<productions.size();i++)
		{
			String prod=(String)productions.get(i);


			if(prod.charAt(0)==p.charAt(0))
			{
				if(prod.charAt(3)=='~')
				flag=true;
				else
				first(prod.substring(3),productions, first,var);
			}

		}
		if(flag)
		{
			if(p.length()>1)
			first(p.substring(1),productions,first,var);
			else
			first[0]+="~";

		}

		return;

	}



	static char availVariable(LinkedList variables)
	{
		for(int i=65;i<=90;i++)
		{
			if(variables.indexOf((char)i)==-1)
			return (char)i;
		}

		return 0;
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
					if(terminals.indexOf(Character.toString(c))==-1)
					terminals.add(Character.toString(temp.charAt(i)));
				}
			}

		}

		System.out.println("Enter the start symbol:");
		String startSymbol=xx.readLine();


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


		//moving start symbol to the front of the list of variables

		variables.addFirst(variables.remove(variables.indexOf(startSymbol)));





		//finding firsts
		String first[]=new String[variables.size()];


		for(int i=0;i<variables.size();i++)
		{
			String temp2[]={""};

			String var=(String)variables.get(i);

			for(int j=0;j<productions.size();j++)
			{
				String prod=(String)productions.get(j);

				if(prod.charAt(0)==var.charAt(0))
				{
					if(prod.charAt(3)=='~')
					{
						if(temp2[0].indexOf("~")==-1)temp2[0]+="~";
					}

					else
					{
						first(prod.substring(3),productions, temp2,var);
					}

				}

			}

			first[i]=temp2[0];

		}

		System.out.println("FIRSTS :");

		for(int i=0;i<variables.size();i++)
		System.out.println((String)variables.get(i) + " : " +  first[i]);



		String follow[]=new String[variables.size()];
		Arrays.fill(follow,"");

		follow[0]+="$";


		for(int i=0;i<variables.size();i++)
		{

			String c=(String)variables.get(i);

			for(int j=0;j<productions.size();j++)
			{
				String temp2[]={""};
				String prod=(String)productions.get(j);

				prod=prod.substring(prod.indexOf("->")+2);

				if(prod.indexOf(c)!=-1 && prod.indexOf(c)!=(prod.length()-1))
				first(prod.substring(prod.indexOf(c)+1),productions,temp2,c);

				if(temp2[0].indexOf("~")!=-1)
				temp2[0]=temp2[0].substring(0,temp2[0].indexOf("~"))+temp2[0].substring(temp2[0].indexOf("~")+1);

				for(int k=0;k<temp2[0].length();k++)
				if(follow[i].indexOf(temp2[0].charAt(k))==-1)
				follow[i]+=temp2[0].charAt(k);
			}

		}

		for(int i=0;i<variables.size();i++)
		{

			String c=(String)variables.get(i);
			String temp2[]={""};

			for(int j=0;j<productions.size();j++)
			{

				String prod=(String)productions.get(j);

				String prod2=prod.substring(prod.indexOf("->")+2);

				if(prod2.indexOf(c)==-1)continue;

				first(prod2.substring(prod2.indexOf(c)+1),productions,temp2,c);

				if((prod2.indexOf(c)==(prod2.length()-1)) || temp2[0].indexOf("~")!=-1)
				{
					for(int k=0;k<follow[variables.indexOf(Character.toString(prod.charAt(0)))].length();k++)
					if(follow[i].indexOf(Character.toString((follow[variables.indexOf(Character.toString(prod.charAt(0)))]).charAt(k)))==-1)
					follow[i]+=(follow[variables.indexOf(Character.toString(prod.charAt(0)))].charAt(k));
				}
			}

		}

		System.out.println("FOLLOWS :");

		for(int i=0;i<variables.size();i++)
		System.out.println((String)variables.get(i) + " : " +  follow[i]);


		//providing for the '$' column
		terminals.add("$");

		String table[][]=new String[variables.size()][terminals.size()];



		for(int i=0;i<variables.size();i++)
		{

			String c=(String)variables.get(i);
			Arrays.fill(table[i],"");


			for(int j=0;j<productions.size();j++)
			{

				String prod=(String)productions.get(j);

				String temp2[]={""};

				String prod2=prod.substring(prod.indexOf("->")+2);

				if(prod.charAt(0)!=c.charAt(0))continue;

				first(prod2,productions, temp2,Character.toString(prod.charAt(0)));
				if(prod2.charAt(0)=='~')
				temp2[0]+="~";

				System.out.println(temp2[0]);

				for(int k=0;k<temp2[0].length();k++)
				{
					if(temp2[0].charAt(k)!='~')
					{
						System.out.println(temp2[0].charAt(k));
						table[i][terminals.indexOf(Character.toString(temp2[0].charAt(k)))]+=" " +prod;
					}
					else
					{
						String fol=follow[variables.indexOf(Character.toString(prod.charAt(0)))];

						for(int l=0;l<fol.length();l++)
						{
							table[i][terminals.indexOf(Character.toString(fol.charAt(l)))]+=prod;
						}
					}

				}

			}

		}

		System.out.print("\t");
		for(int i=0;i<terminals.size();i++)
		System.out.print(terminals.get(i)+"\t");

		System.out.println();


		for(int i=0;i<variables.size();i++)
		{
			System.out.print(variables.get(i)+"\t");

			for(int j=0;j<terminals.size();j++)
			System.out.print(table[i][j]+"\t");

			System.out.println();
		}


		//System.out.println(Arrays.deepToString(table));

	}

}






