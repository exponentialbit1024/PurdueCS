# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def map_coord_pair_move(cA, cB):
    dx = cA[0] - cB[0]
    dy = cA[1] - cB[1]
    return [dx, dy]

def generic_search(problem, algorithm, heuristic=0):
    visited_nodes = dict()
    state = problem.getStartState()

    node = {'state' : state, 'parent' : None, 'move' : None, 'cost' : 0}
    if algorithm == 'dfs':
        fringe = util.Stack()
        fringe.push(node)
    elif algorithm == 'bfs':
        fringe = util.Queue()
        fringe.push(node)
    elif algorithm == 'ucs' or algorithm == 'astar':
        fringe = util.PriorityQueue()
        if algorithm == 'astar':
            node["eval"] = heuristic(state, problem)
            fringe.push(node, node["cost"] + node["eval"])
        else:
            fringe.push(node, node["cost"])


    while not fringe.isEmpty():
        node = fringe.pop()
        state = node['state']
        if algorithm == 'ucs':
            cost = node['cost']
        elif algorithm == 'astar':
            cost = node['cost']
            node_ev = node["eval"]
        if visited_nodes.has_key(hash(state)):
            continue

        visited_nodes[hash(state)] = True
        if problem.isGoalState(state) == True:
            break

        successors = problem.getSuccessors(state)
        for successor in successors:
            if not visited_nodes.has_key(hash(successor[0])):
                if algorithm == 'ucs':
                    child = {'state' : successor[0], 'parent' : node, 'move' : successor[1], 'cost' : successor[2] + cost}
                    fringe.push(child, child['cost'])
                elif algorithm == 'astar':
                    child = {'state' : successor[0], 'parent' : node, 'move' : successor[1], 'cost' : successor[2] + cost, 'eval' : heuristic(successor[0], problem)}
                    fringe.push(child, child['cost'] + child['eval'])
                else:
                    child = {'state' : successor[0], 'parent' : node, 'move' : successor[1]}
                    fringe.push(child)

    move_list = []
    while not node['state'] == problem.getStartState():
        move_list.insert(0, node['move'])
        node = node['parent']

    return move_list


def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"
    return generic_search(problem, 'dfs')

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    # util.raiseNotDefined()
    return generic_search(problem, 'bfs')

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    # util.raiseNotDefined()
    return generic_search(problem, 'ucs')

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    # util.raiseNotDefined()
    return generic_search(problem, 'astar', heuristic)

# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
