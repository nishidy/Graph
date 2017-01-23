import scala.collection.mutable.ArrayBuffer
import scala.collection.mutable.HashMap
import scala.collection.mutable.PriorityQueue

class Node(val id:Int) {
	var from_id:Int = -1;
	var cost:Int = dijkstra.INF;
	var edges_to=ArrayBuffer.empty[Int]
	var edges_cost=ArrayBuffer.empty[Int]
}

object Comp extends Ordering[Node]{
	def compare(x:Node, y:Node)=y.cost.compare(x.cost);
}

object dijkstra {
	val INF = 1<<20;

	def main(args: Array[String]) {

		//println("Hello world!");
		var nodes=HashMap.empty[Int,Node]

		var T:Int = readLine.toInt;
		for(i:Int <- 1 to T){
			//in = readLine.split(" ").map(_.toInt);
			val sc=new java.util.Scanner(System.in);
			val n,t,c=sc.nextInt;

			var node:Node = nodes(n);
			if(node.type==None){
				node = new Node(n);
				nodes += (n->node)
			}
			node.edges_to+=t
			node.edges_cost+=c

		}
		val sc=new java.util.Scanner(System.in);
		val s,g=sc.nextInt;

		var pq=new PriorityQueue[Node]()(Comp);

		var node:Node = pq.head;
		while(!pq.isEmpty){

			for((i,j)<-node.edges_to.zip(node.edges_cost)){

			}

		}

	}

}


