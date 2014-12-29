import java.util.*;
import java.io.*;

class dijkstra {

	static class Node{

		int id;
		int from_id;
		List<Integer> edges_to;
		List<Integer> edges_cost;

		boolean done;
		int cost;

		Node(int id){
			this.id=id;
			this.from_id=-1;
			this.done=false;
			this.cost=MAX;

			edges_to = new ArrayList<Integer>();
			edges_cost = new ArrayList<Integer>();
		}

	}

	public static class compClass implements Comparator<Node> {

		// Sorts so that this returns minus (-1)
		public int compare(Node node1, Node node2){
			if(node1.cost>node2.cost){
				return 1;
			}else if(node1.cost<node2.cost){
				return -1;
			}else{
				return 0;
			}
		}
	}

	public static boolean finish(){
		for(Iterator<Map.Entry<Integer,Node>> it=nodes.entrySet().iterator();
			it.hasNext(); ){
			Map.Entry<Integer,Node> entry=it.next();
			if(entry.getValue().done==false) return false;
		}
		return true;
	}

	public static Map<Integer,Node> nodes = new HashMap<Integer,Node>();
	public static final int MAX=1<<20;

	public static void main(String[] argv) throws java.io.IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("[Shortest path search by dijkstra algorithm]\n");

		int T = Integer.parseInt(br.readLine());

		int f,t,c;
		String str[];
		for(int i=0;i<T;++i){
		    str = br.readLine().split(" ");
			f=Integer.parseInt(str[0]);
			t=Integer.parseInt(str[1]);
			c=Integer.parseInt(str[2]);

			Node node;
			if(nodes.containsKey(f)){
				node=nodes.get(f);
			}else{
				node=new Node(f);
				nodes.put(f,node);
			}
			node.edges_to.add(t);
			node.edges_cost.add(c);

			if(nodes.containsKey(t)){
				node=nodes.get(t);
			}else{
				node=new Node(t);
				nodes.put(t,node);
			}
			node.edges_to.add(f);
			node.edges_cost.add(c);
		}

		int s,g;
		str= br.readLine().split(" ");
		s=Integer.parseInt(str[0]);
		g=Integer.parseInt(str[1]);

		Queue<Node> pq = new PriorityQueue<Node>(1, new compClass());

		Node node;
		node=nodes.get(s);
		node.cost=0;
		pq.add(node);

		Node next;
		int cost;

		while(!pq.isEmpty()){
			node=pq.poll();
			if(node.done) continue;
			node.done=true;

			if(finish()) break;

			for(int i=0;i<node.edges_to.size();++i){
				cost=node.cost+node.edges_cost.get(i);
				next=nodes.get(node.edges_to.get(i));
				if(cost<next.cost){
					next.from_id=node.id;
					next.cost=cost;
					pq.add(next);
				}
			}
		}

		System.out.printf("Min cost is %d ",nodes.get(g).cost);

		node=nodes.get(g);
		List<Integer> min_path_nodes=new ArrayList<Integer>();
		while(true){
			min_path_nodes.add(node.id);
			node=nodes.get(node.from_id);
			if(node==null){
				System.out.print("(");
				Collections.reverse(min_path_nodes);
				for(int i=0;i<min_path_nodes.size();++i){
					if(i>0) System.out.printf("->");
					System.out.print(min_path_nodes.get(i));
				}
				System.out.print(")\n");
				break;
			}
		}

	}

}


