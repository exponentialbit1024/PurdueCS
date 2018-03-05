# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        foodList = newFood.asList()
        availFood = len(foodList)
        nearestDist = float("inf")
        for i in range(availFood):
            distToFood = manhattanDistance(foodList[i], newPos) + 50 * availFood
            if distToFood < nearestDist:
                nearestDist = distToFood
                closestFood = foodList
        if availFood == 0:
            nearestDist = 0
        score = -nearestDist

        for j in range(len(newGhostStates)):
            if newGhostStates[j].scaredTimer <= 0:
                ghostPosition = successorGameState.getGhostPosition(j + 1)
                if manhattanDistance(newPos, ghostPosition) <= 1:
                    score -= float("inf")
            else:
                score -= 10

        # return successorGameState.getScore()
        return score

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        possibleMoves = gameState.getLegalActions() #pacmans actions
        nodes = [gameState.generateSuccessor(0, action) for action in possibleMoves]
        bestMove = self.minimax(gameState, nodes)
        return possibleMoves[bestMove]
        # util.raiseNotDefined()

    def minimax(self, gameState, nodes):
        scores = [self.minimizer(state, 0, 1) for state in nodes]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index]==bestScore]
        chosenIndex = random.choice(bestIndices)
        return chosenIndex

    def maximizer(self, gameState, depth):
        if self.depth == depth or gameState.isLose() or gameState.isWin():
            return self.evaluationFunction(gameState)
        maxMoves = gameState.getLegalActions(0)
        possibleMaxStates = [gameState.generateSuccessor(0, action) for action in maxMoves]
        scores = [self.minimizer(state, depth, 1) for state in possibleMaxStates]
        return max(scores)

    def minimizer(self, gameState, depth, ghostIndex):
        if self.depth == depth or gameState.isLose() or gameState.isWin():
            return self.evaluationFunction(gameState)

        minMoves = gameState.getLegalActions(ghostIndex)
        possibleMinStates = [gameState.generateSuccessor(ghostIndex, action) for action in minMoves]
        if ghostIndex >= gameState.getNumAgents() - 1:
            scores = [self.maximizer(state, depth + 1) for state in possibleMinStates]
        else:
            scores = [self.minimizer(state, depth, ghostIndex + 1) for state in possibleMinStates]

        return min(scores)

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"

        depth = self.depth*gameState.getNumAgents()
        legalActions = gameState.getLegalActions()
        bestaction = Directions.STOP
        score = -(float("inf"))
        alpha = -(float("inf"))
        beta = (float("inf"))
        for action in legalActions:
            nextState = gameState.generateSuccessor(0, action)
            prevscore = score

            score = max(score, self.minimizer(nextState, depth - 1, 1, alpha, beta))
            if score > prevscore:
                bestaction = action
            if score > beta:
                return bestaction
            alpha = max(alpha, score)
        return bestaction
        util.raiseNotDefined()

    def maximizer(self, gameState, depth, alpha, beta):
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.evaluationFunction(gameState)

        score = float("-inf")
        possibleMoves = gameState.getLegalActions(0)
        for move in possibleMoves:
            score = max(score, self.minimizer(gameState.generateSuccessor(0, move), depth - 1, 1, alpha, beta))
            if score > beta:
                return score
            alpha = max(alpha, score)
        return score

    def minimizer(self, gameState, depth, ghostIndex, alpha, beta):
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.evaluationFunction(gameState)

        score = float("inf")
        possibleMoves = gameState.getLegalActions(ghostIndex)
        for move in possibleMoves:
            if ghostIndex == gameState.getNumAgents() - 1:
                score = min(score, self.maximizer(gameState.generateSuccessor(ghostIndex, move), depth - 1, alpha, beta))
            else:
                score = min(score, self.minimizer(gameState.generateSuccessor(ghostIndex, move), depth - 1, ghostIndex + 1, alpha, beta))
            if score < alpha:
                return score
            beta = min(beta, score)
        return score

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        possibleMoves = gameState.getLegalActions() #pacmans actions
        nodes = [gameState.generateSuccessor(0, action) for action in possibleMoves]
        bestMove = self.expectimax(gameState, nodes)
        return possibleMoves[bestMove]
        util.raiseNotDefined()

    def expectimax(self, gameState, nodes):
        scores = [self.minimizer(state, 0, 1) for state in nodes]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index]==bestScore]
        chosenIndex = random.choice(bestIndices)
        return chosenIndex

    def maximizer(self, gameState, depth):
        if self.depth == depth or gameState.isLose() or gameState.isWin():
            return self.evaluationFunction(gameState)
        maxMoves = gameState.getLegalActions(0)
        possibleMaxStates = [gameState.generateSuccessor(0, action) for action in maxMoves]
        scores = [self.minimizer(state, depth, 1) for state in possibleMaxStates]
        return max(scores)

    def minimizer(self, gameState, depth, ghostIndex):
        if self.depth == depth or gameState.isLose() or gameState.isWin():
            return self.evaluationFunction(gameState)

        minMoves = gameState.getLegalActions(ghostIndex)
        possibleMinStates = [gameState.generateSuccessor(ghostIndex, action) for action in minMoves]
        if ghostIndex >= gameState.getNumAgents() - 1:
            scores = [self.maximizer(state, depth + 1) for state in possibleMinStates]
        else:
            scores = [self.minimizer(state, depth, ghostIndex + 1) for state in possibleMinStates]

        return sum(scores) / len(scores)

def ghostPositions(pos, ghosts):
    return map(lambda g: manhattanDistance(pos, g.getPosition()), ghosts)

def capsuleDistance(pos, capsuleCoords):
    distances = []
    for coord in capsuleCoords:
        distances.append(manhattanDistance(pos, coord))
    return sum(distances)

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    currPos = currentGameState.getPacmanPosition()
    currScore = scoreEvaluationFunction(currentGameState)
    if currentGameState.isLose():
        return float("-inf")
    if currentGameState.isWin():
        return float("inf")

    food = currentGameState.getFood().asList()
    foodDist = min(map(lambda x: manhattanDistance(currPos, x), food))
    numFood = len(food)

    capsules = currentGameState.getCapsules()
    numCaps = len(capsules)

    ghosts = currentGameState.getGhostStates()
    activeGhost, passiveGhost = [], []
    for ghost in ghosts:
        if not ghost.scaredTimer:
            activeGhost.append(ghost)
        else:
            passiveGhost.append(ghost)

    activeGdist = 0
    passiveGdist = 0

    if activeGhost:
        activeGdist = min(ghostPositions(currPos, activeGhost))
    else:
        activeGdist = float("inf")

    activeGdist = max(activeGdist, 5)

    if passiveGhost:
        passiveGdist = min(ghostPositions(currPos, passiveGhost))
    else:
        passiveGdist = 0

    return currScore - 1.5 * foodDist - 2 * (1. / activeGdist) - 2 * passiveGdist - 20 * numCaps - 4 * numFood
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
