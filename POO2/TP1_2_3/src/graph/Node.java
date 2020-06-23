package graph;

import java.util.Vector;

public class Node<T> {
    private T value;
    private Vector<Node<T>> targets;
    
    
    public static void main(String[] args)  {
        Graph<Integer> graph = new Graph<Integer>(1);
        Node<Integer> node_2 = new Node<Integer>(2);
        Node<Integer> node_3 = new Node<Integer>(3);
        Node<Integer> node_4 = new Node<Integer>(4);


        graph.addTargets( node_3);
        node_2.addTargets(node_2);
        node_3.addTargets(node_4);

        System.out.println(graph.maxNodesTillEnd());
        System.out.println(graph.browse());
    }
    
    
    public Node() {
        targets = new Vector<Node<T>>();
    };
    
    public Node(T value) {
        this();
        this.value = value;
    }
    
    public Node<T> addTarget(Node<T> ptarget) {
        targets.add(ptarget);
        return this;
    }
    
    @SafeVarargs
    final public void addTargets(Node<T>... ptargets) {
        for (Node<T> ptarget : ptargets) {
            addTarget(ptarget);
        }
    }

    public Vector<Node<T>> getTargets() {
        return targets;
    }

    public Node<T> getTarget(int i) {
        if (i >= targets.size())
            return null;
        return targets.elementAt(i);
    }

    public void resetTargets() {
        targets.clear();
    }

    public T setValue(T value) {
        return this.value = value;
    }

    public T getValue() {
        return value;
    }

    public String toString() {
        return value.toString();
    }

    public int maxNodesTillEnd() {
        if (targets.isEmpty())
            return 1;
        int currentMax = 0;
        for (Node<T> node : targets) {
            Integer tmp = node.maxNodesTillEnd();
            if(tmp > currentMax)
                currentMax = tmp;
        }
        return currentMax+1;
    }

    public String browse() {
        String result = this.getValue().toString();
        for (Node<T> node : targets) {
            result += ", ";
            result += node.browse();
        }
        return result;
    }
}