
class Node
    def initialize(node_id)
        @id = node_id 
        @edges = {}
    end

    def add_edge(to,cost)
        @edges[to]= cost
    end

    def get_edges
        @edges
    end

    def get_id
        @id
    end
end

class Graph
    def initialize
        @nodes = {}
    end

    def add_node(node_id)
        unless !@nodes.nil? and @nodes.key? node_id 
            @nodes[node_id] = Node.new(node_id)
        end
    end
    def add_edge(from,to,cost)
        @nodes[from].add_edge(to,cost)
    end
end


class Heap

    def initialize
        @heap = []
        @num_heap = 0
    end

    def push(node,key)
        idx = @num_heap
        @heap[idx] = node

        while 0<idx do
            up_idx = (idx-1)/2
            if @heap[idx][key] < @heap[up_idx][key]
                @heap[up_idx], @heap[idx] = @heap[idx], @heap[up_idx]
            end
            idx = up_idx
        end
        @num_heap+=1
    end

    def pop(key)
        top = @heap[0].dup
        @heap[0] = @heap[@num_heap-1]
        @num_heap-=1
        #debug(key)

        idx = 0
        while idx<@num_heap do
            left_idx = idx*2+1
            right_idx = left_idx+1

            if @num_heap-1 < left_idx
                break
            elsif @num_heap-1 == left_idx
                smaller_idx = left_idx
            elsif left_idx < @num_heap-1
                if @heap[left_idx][key] < @heap[right_idx][key]
                    smaller_idx = left_idx
                else
                    smaller_idx = right_idx
                end
            end

            @heap[smaller_idx],@heap[idx] = @heap[idx],@heap[left_idx]
            idx = smaller_idx
        end
        #debug(key)
        top
    end

    def top
        @heap[0]
    end

    def empty?
        @num_heap == 0
    end

    def debug(key)
        puts @heap.each.map{|a|a[key]}.reduce{|a,b|"#{a} #{b}"}
    end
end

class Dijkstra < Graph

    @@ManageNode = Struct.new(:node, :cost, :done, :from)

    def initialize()
        super()
        @man_nodes= {}
        @start = 0
        @goal = 0
        @pq_nodes = Heap.new()
    end

    def init_man_nodes
        @nodes.each {|node_id,node|
            @man_nodes[node_id] = @@ManageNode.new(node,1<<30,false,-1)
        }
    end

    def update_man_node(node_id,cost,from)
        @man_nodes[node_id][:cost] = cost
        @man_nodes[node_id][:from] = from
    end

    def enque_man_node(node_id)
        @pq_nodes.push(@man_nodes[node_id],:cost)
    end

    def get_man_node_cost(node_id)
        @man_nodes[node_id][:cost]
    end

    def done?(node_id)
        @man_nodes[node_id][:done]
    end

    def save_done(node_id)
        @man_nodes[node_id][:done] = true
    end

    def solve(start,goal)
        @start = start
        @goal = goal
        puts "#{start} ---> #{goal}"

        init_man_nodes
        update_man_node(@start,0,-1)
        enque_man_node(@start)

        to_goal_cost = 0
        c=0
        while !@pq_nodes.empty? do
            c+=1
            node = @pq_nodes.top[:node]
            cost = @pq_nodes.top[:cost]
            node_id = node.get_id()
            @pq_nodes.pop(:cost)

            if done?(node_id)
                next
            else
                save_done(node_id)
            end

            if node_id == @goal
                to_goal_cost = cost
                break
            end

            node.get_edges().each {|to_node_id,to_cost|
                new_cost = cost + to_cost
                if new_cost < get_man_node_cost(to_node_id)
                    update_man_node(to_node_id, new_cost, node_id)
                    enque_man_node(to_node_id)
                end
            }
        end

        puts "cost : #{to_goal_cost}"
    end

    def show_path
        print "path : "
        path = []
        node_id = @goal
        while 0 <= node_id do 
            man_node = @man_nodes[node_id]
            path << node_id
            break if node_id == @start
            node_id = man_node[:from]
        end
        puts path.reverse.each.reduce {|a,b| "#{a} -> #{b}" }
    end

end

if __FILE__ == $0

    graph = Dijkstra.new()
    start=goal=0

    if ARGV.size() == 1
        open(ARGV[0],"r") { |file|
            graph = nil
            file.each_line { |line|
                case file.lineno
                when 1 then
                    num_nodes,num_edges = line.split.map{|i|i.to_i}
                when 2 then
                    start,goal = line.split.map{|i|i.to_i}
                else
                    from_node, to_node, edge_cost = line.split.map{|i|i.to_i}
                    graph.add_node(from_node)
                    graph.add_node(to_node)
                    graph.add_edge(from_node,to_node,edge_cost)
                end
            }
        
        }
    else
        _,num_edges = $stdin.gets.split.map{|i|i.to_i}
        start,goal = $stdin.gets.split.map{|i|i.to_i}
        (0...num_edges).each{
            from_node, to_node, edge_cost = $stdin.gets.split.map{|i|i.to_i}
            graph.add_node(from_node)
            graph.add_node(to_node)
            graph.add_edge(from_node,to_node,edge_cost)
        }
    end

    graph.solve(start,goal)
    graph.show_path()

end 

