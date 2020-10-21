package main

import (
	"errors"
	"fmt"
	"strconv"
	"strings"

	"./stack"
)

// GetPostfixExpr returns expr in postfix form
func GetPostfixExpr(infixExpr string) (string, error) {

	st := stack.NewStack()
	for _, c := range infixExpr {
		cc := string(c)
		if cc == "(" {
			st.Push(stack.NewStackElement(cc))
		}
		if cc == ")" {
			if st.Length() > 0 {
				_ = st.Pop()
			} else {
				return "", errors.New("expressionError: brackets must be paired")
			}
		}
	}

	if st.Length() > 0 {
		return "", errors.New("expressionError: brackets must be paired")
	}

	infixExpr = strings.Replace(infixExpr, " ", "", -1)
	infixExpr = strings.Replace(infixExpr, "+", ",+,", -1)
	infixExpr = strings.Replace(infixExpr, "-", ",-,", -1)
	infixExpr = strings.Replace(infixExpr, "*", ",*,", -1)
	infixExpr = strings.Replace(infixExpr, "/", ",/,", -1)
	infixExpr = strings.Replace(infixExpr, "(", ",(,", -1)
	infixExpr = strings.Replace(infixExpr, ")", ",),", -1)

	tempInfix := strings.Split(infixExpr, ",")

	st = stack.NewStack()
	postfixExpr := []string{}
	for _, str := range tempInfix {
		switch string(str) {
		case "(":
			st.Push(stack.NewStackElement(string(str)))
			break
		case ")":
			for {
				if st.Length() == 0 {
					break
				}
				s := st.Pop()
				if s.Value == "(" {
					break
				}
				postfixExpr = append(postfixExpr, s.Value)
			}
			break
		case "+", "-", "*", "/":
			for {
				if st.Length() == 0 || st.Head.Value == "(" {
					break
				}
				if string(str) == "/" && (st.Head.Value == "*" || st.Head.Value == "+" || st.Head.Value == "-") {
					break
				}
				if string(str) == "*" && (st.Head.Value == "+" || st.Head.Value == "-") {
					break
				}
				s := st.Pop()

				postfixExpr = append(postfixExpr, s.Value)
			}
			st.Push(stack.NewStackElement(string(str)))
			break
		default:
			if string(str) == "" {
				continue
			}
			postfixExpr = append(postfixExpr, string(str))
		}
	}
	for st.Length() > 0 {
		s := st.Pop()
		postfixExpr = append(postfixExpr, s.Value)
	}
	return strings.Join(postfixExpr, " "), nil
}

// SolvePostfix solves postfix expression
func SolvePostfix(postfix string) (string, error) {

	expr := strings.Split(postfix, " ")
	st := stack.NewStack()

	for _, el := range expr {
		if el == "+" || el == "-" || el == "*" || el == "/" {
			el1, _ := strconv.ParseFloat(st.Pop().Value, 64)
			el2, _ := strconv.ParseFloat(st.Pop().Value, 64)
			var result float64
			switch el {
			case "+":
				result = el1 + el2
			case "-":
				result = el2 - el1
			case "*":
				result = el1 * el2
			case "/":
				if el1 == 0 {
					return "", errors.New("typeError: division by zero")
				}
				result = el2 / el1
			}
			st.Push(stack.NewStackElement(fmt.Sprintf("%f", result)))
		} else {
			st.Push(stack.NewStackElement(el))
		}
	}
	return st.Pop().Value, nil
}

//CalculateExpression calculates given expression, returns solution or error
func CalculateExpression(expression string) (string, error) {
	postfixExpr, err := GetPostfixExpr(expression)
	if err != nil {
		return "", err
	}
	return SolvePostfix(postfixExpr)
}

func main() {
	val, _ := CalculateExpression("2+2*2")
	fmt.Println(val) //should output 6 to the terminal
}
