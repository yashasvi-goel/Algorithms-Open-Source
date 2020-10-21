package stack

type Stack struct {
	len  int
	Head *StackElement
}

func NewStack() *Stack {
	return &Stack{
		Head: nil,
		len:  0,
	}
}

type StackElement struct {
	Value string
	Next  *StackElement
}

func NewStackElement(val string) *StackElement {
	return &StackElement{
		Value: val,
		Next:  nil,
	}
}

func (s *Stack) Push(elem *StackElement) {
	elem.Next = s.Head
	s.Head = elem
	s.len++
}

func (s *Stack) Pop() *StackElement {
	cur := s.Head
	s.Head = s.Head.Next
	s.len--
	return cur
}

func (s *Stack) Length() int {
	return s.len
}
