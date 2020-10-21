package main

import (
	"errors"
	"testing"

	"github.com/stretchr/testify/assert"
)

type testSuite struct {
	expr   string
	answer string
	err    error
}

func TestGetPostfixExpr(t *testing.T) {
	t.Parallel()
	infixExpr := "2+2"
	postfix, err := GetPostfixExpr(infixExpr)
	assert.Equal(t, "2 2 +", postfix)
	assert.Equal(t, nil, err)

}

func TestCalculateEasyExpressions(t *testing.T) {
	t.Parallel()
	tSuite := []testSuite{
		{expr: "2 + 2", answer: "4.000000", err: nil},
		{expr: "2-2", answer: "0.000000", err: nil},
		{expr: "2*3", answer: "6.000000", err: nil},
		{expr: "1/2", answer: "0.500000", err: nil},
		{expr: "1 / 0", answer: "", err: errors.New("typeError: division by zero")},
		{expr: " 49 * 63 / 58 * 36 ", answer: "1916.069148", err: nil},
		{expr: " 84 + 62 / 33 * 10 + 15 ", answer: "117.787880", err: nil},
		{expr: " 48 + 59 * 86 * 92 * 23 ", answer: "10736632.000000", err: nil},
		{expr: " 16 + 25 - 92 + 54 / 66 ", answer: "-50.181818", err: nil},
		{expr: " 64 + 19 - 77 - 93 ", answer: "-87.000000", err: nil},
		{expr: " 88 - 72 + 55 * 57", answer: "3151.000000", err: nil},
		{expr: " 99 * 55 / 30 + 50 ", answer: "231.499967", err: nil},
		{expr: " 11 - 88 + 84 - 48 ", answer: "-41.000000", err: nil},
		{expr: " 68 * 60 / 87 / 53 + 17 ", answer: "17.884816", err: nil},
		{expr: " 63 - 69 - 46 + 57 ", answer: "5.000000", err: nil},
		{expr: " 60 + 29 / 57 - 85 ", answer: "-24.491228", err: nil},
		{expr: " 34 * 18 * 55 - 50 ", answer: "33610.000000", err: nil},
		{expr: " 12 * 3 - 18 + 34 - 84 ", answer: "-32.000000", err: nil},
		{expr: " 70 / 42 - 52 - 64 / 35 ", answer: "-52.161904", err: nil},
		{expr: " 39 / 41 + 100 + 45 ", answer: "145.951220", err: nil},
	}

	for _, c := range tSuite {
		result, err := CalculateExpression(c.expr)
		assert.Equal(t, c.err, err)
		assert.Equal(t, c.answer, result)
	}
}

func TestCalculateMediumExpressions(t *testing.T) {
	t.Parallel()
	tSuite := []testSuite{
		{expr: "1 + 2) * 3", answer: "", err: errors.New("expressionError: brackets must be paired")},
		{expr: "((1 + 2) * 3", answer: "", err: errors.New("expressionError: brackets must be paired")},
		{expr: "((1 + 2 * 3", answer: "", err: errors.New("expressionError: brackets must be paired")},

		{expr: " 20 - 57 * 12 - (  58 + 84 * 32 / 27  ) ", answer: "-821.555540", err: nil},
		{expr: " 77 + 79 / 25 * (  64 * 63 - 89 * 14  ) * 49 ", answer: "431461.240000", err: nil},

		{expr: " 100 - 60 / 38 + (  19 / 88 * 97 / 82 / 94  ) * 92 ", answer: "98.671017", err: nil},
		{expr: " (  97 / 48 + 86 + 56 * 94  ) / 43 + 57 ", answer: "181.465601", err: nil},
		{expr: " (  68 - 85 / 75 * 64  ) / 15 + 73 ", answer: "72.697779", err: nil},

		{expr: " 91 + 18 / (  42 + 62 + 84 * 95  ) + 30 ", answer: "121.002227", err: nil},
		{expr: " 49 * 31 * (  20 - 83 / 63 / 46 * 29  ) / 68 ", answer: "428.212176", err: nil},
		{expr: " 35 - 45 / 37 + 84 + (  41 + 86 / 18 / 41 * 73  ) ", answer: "167.290547", err: nil},

		{expr: " 44 * 13 / (  26 + 24 * 70 + 89 * 7  ) + 81 ", answer: "81.245608", err: nil},
		{expr: " 53 - 88 + 7 + (  34 / 54 + 15 / 23 / 6  ) * 73 ", answer: "25.897798", err: nil},
		{expr: " 57 - 71 + (  14 + 3 - 24 * 100 / 23  ) / 53 ", answer: "-15.648072", err: nil},

		{expr: " (  41 * 76 * 79 - 61  ) / 60 + 83 ", answer: "4184.716667", err: nil},
		{expr: " (  73 + 85 + 64 / 17  ) * 17 + 31 / 60 ", answer: "2750.516669", err: nil},
		{expr: " 74 * 96 + 62 / (  25 / 33 + 96 + 87 + 78  ) ", answer: "7104.236860", err: nil},

		{expr: " 33 - 96 + (  95 - 76 * 98 / 11  ) * 15 ", answer: "-8794.363740", err: nil},
		{expr: " 72 / 75 + 4 * (  14 * 2 / 57 * 21  ) / 15 ", answer: "3.710900", err: nil},
		{expr: " 72 * 95 + 53 + (  2 + 76 - 52 / 1 - 47  ) ", answer: "6872.000000", err: nil},

		{expr: " 85 * 97 / (  89 / 11 - 18 * 96  ) - 61 ", answer: "-65.793830", err: nil},
		{expr: " 29 + 24 / 91 - (  14 * 71 * 18 / 20 * 100  ) + 63 ", answer: "-89367.736264", err: nil},
		{expr: " 52 * 62 * (  61 + 12 - 14 * 79  ) + 39 ", answer: "-3330353.000000", err: nil},
	}

	for _, c := range tSuite {
		result, err := CalculateExpression(c.expr)
		assert.Equal(t, c.err, err)
		assert.Equal(t, c.answer, result)
	}
}

func TestCalculateHardExpressions(t *testing.T) {
	t.Parallel()
	tSuite := []testSuite{
		{expr: " (  38 + 52 + 65 - 19  ) * (  72 * 3 / 36 * (  9 / 2 - 17 * 38 / 28  )  ) / 18 / 84 ", answer: "-10.022656", err: nil},
		{expr: " 93 * 30 / 81 * (  78 * 83 / (  71 * 13 - (  14 + 13 - 28 * 62  ) * 62  ) + 99 - (  80 - 89 + 17 * 42  )  ) ", answer: "-20871.224922", err: nil},
		{expr: " 58 * 85 * (  1 + 16 * 7 + (  82 * 31 * (  85 / 75 - 51 - 22  ) + 2 - 24  )  ) * 22 * (  27 + 67 + 0 + 93  ) ", answer: "-3703376529200.298340", err: nil}, //-3703376512014.6670

		{expr: " 99 - 78 * (  (  (  63 + 52 / 67 + 26 / 29  ) + 94 + (  68 - 11 / 1 * 88  ) + 49  ) / 69 * 15 * 8  ) - 1 ", answer: "94013.703440", err: nil},
		{expr: " (  56 / 33 + 87 + (  (  12 / 48 - 44 - 51  ) + 85 * (  69 - 35 - 67 - 82 + 81  ) - 40  )  ) - 86 - 85 ", answer: "-3107.053030", err: nil},
		{expr: " (  80 / 12 / 47 - 93  ) + 78 / (  20 / 23 + (  54 + 36 / 29 + 23  ) - 61  ) ", answer: "-88.551368", err: nil},

		{expr: " (  (  91 / 57 / 30 - 72  ) - (  53 * 22 / 23 / 6  ) * 79 - 27  ) - 19 / 30 ", answer: "-767.071657", err: nil},
		{expr: " (  36 + 78 + (  43 / 89 - 57 / (  64 + 98 / 57 - 24 - 47  )  ) * 56  ) - (  (  29 - 9 / 76 * 99 - 29  ) * 98 / 11  ) * 31 ", answer: "3983.388253", err: nil},
		{expr: " 6 + 78 + (  55 / 20 - 92 / 55 / (  (  94 + 40 + 56 / 61  ) / 38 / 97 + (  32 / 36 / 25 * (  12 / 30 - 22 * (  51 / 87 * 71 / 50 / (  98 - 37 - 90 - 91  )  )  ) * 57  )  )  ) / 42 / 25 ", answer: "84.001242", err: nil},

		{expr: " (  (  60 - 42 - 16 / 100  ) * (  29 * 88 + 51 + 77  ) - 49 - 59  ) - 89 * 45 ", answer: "43698.200000", err: nil},
		{expr: " 11 - 92 + 48 / (  (  12 / 92 + (  53 / 74 / 22 + (  61 / 24 / 42 - (  13 * 85 + 100 / 77 / 11  ) + 89  ) + 9  ) + 87  ) / 91 * 92  ) ", answer: "-81.051613", err: nil},
		{expr: " 66 - 83 + (  (  41 * 98 * 10 * (  40 / 64 + 46 * 33  )  ) / (  61 + 91 - 73 * 9 + 12  ) / (  88 * 29 / 96 - 41 - 72  )  ) * (  81 * 40 / 95 + 61  ) + 5 ", answer: "136201.636802", err: nil},

		{expr: " (  93 * 79 / (  24 + 83 / (  11 * 45 / 21 * (  (  75 - 15 - (  60 + 94 / (  70 - 27 - 89 + 71  ) - 81  ) * 27 - 73  ) * 92 - 59 - 57  ) + 13  ) * 84 * 49  ) / 22  ) * 27 / 62 + 76 ", answer: "81.972577", err: nil},
		{expr: " (  (  18 - 15 + 90 + 68 / 71  ) - 94 + (  51 / 67 + 12 / 39 + 15  ) - 28  ) + 14 / 97 ", answer: "-11.829038", err: nil},
		{expr: " 29 + 67 - 22 * (  (  (  98 + 90 * 90 + 81 - 83  ) * 92 - 79 + 37  ) * 20 - 60  ) ", answer: "-331754184.000000", err: nil},

		{expr: " 92 - 34 + 32 * (  (  (  89 - 87 / 11 / 66  ) / 49 + 2 / 76  ) / 93 / 45  ) * 92 ", answer: "59.295360", err: nil}, //59.2945
		{expr: " (  81 + 60 / 54 / 21  ) + (  77 - 31 + (  41 + 69 - 62 - 96  ) * 0  ) - 0 - 62 ", answer: "65.052910", err: nil},
		{expr: " 20 * 60 + 9 - (  89 * 95 * 3 * (  44 - 51 - 11 - (  62 + 69 - 22 + 21  ) * 9  ) / 50  ) - (  94 - 70 / 29 / 7  ) ", answer: "603787.744828", err: nil},

		{expr: " 94 / 49 + 36 / (  39 + 1 - (  18 * 47 / 20 * (  66 - 51 / 19 / 19 + (  22 * 80 / 4 / 74 - 59  )  ) * 12  ) / 69  ) ", answer: "1.254133", err: nil},
		{expr: " 24 - 23 * 17 / (  93 + 52 * 70 * (  6 + 91 / (  (  4 / 39 / 8 * 30  ) / (  22 * 97 * (  32 * 20 * (  82 - 80 * 51 / 89 * 9  ) * 56 + 82  ) * 89  ) - 17 - 17  ) / 29 / 81  )  ) ", answer: "23.982175", err: nil},
		{expr: " 3 * 26 / (  (  75 / 18 * 91 * 38  ) / 53 - (  52 / 34 - (  10 * 67 - 50 - 78  ) * 51 + 58  )  ) + 73 ", answer: "73.002799", err: nil},

		{expr: " (  91 / 56 + 53 * 93  ) + (  12 * 36 + 55 + 54 / (  56 + 43 + 45 + 61 - 45  )  ) / (  94 - 23 - 66 * (  71 + 65 / 95 / 27 / 1  ) - 17  ) ", answer: "4930.519827", err: nil},
		{expr: " 75 * 97 * 3 - (  (  59 - 3 / 88 + (  93 * 100 * 65 - 38 + 54  )  ) / 63 - 85  ) ", answer: "12313.571970", err: nil},
		{expr: " (  94 / 78 / 20 / 62  ) + 78 - (  (  40 + 46 / 7 * 35  ) / 42 + 41 * 26  ) ", answer: "-994.427600", err: nil},

		{expr: " (  6 + 28 + 18 - (  (  61 + 17 * 64 * 98  ) * (  61 / 53 * 47 / 36 * 98  ) + 82 + (  69 - 55 / (  62 * 77 / 88 - 52 / 10  ) - 42 - (  48 / 84 * 77 + 40 - 13  )  )  )  ) - 4 / 99 ", answer: "-15710082.814796", err: nil}, //-15710078.0585
		{expr: " 96 * 67 - 10 + (  40 - 42 - 25 / (  96 / 23 * 54 * (  18 * 30 / 85 / 79 - 90  )  )  ) ", answer: "6420.001234", err: nil},
		{expr: " 93 - 42 / (  80 * 45 + 46 + (  66 * 45 - 26 * 0 * 84  )  ) - (  (  20 - 59 - 18 - 62  ) / (  9 / 90 * 16 - 6  ) * 3  ) ", answer: "11.857287", err: nil},

		{expr: " 31 * 21 + 14 / (  (  18 * 52 / (  43 - 74 / 89 - 12  ) + 8  ) + 3 / 0 + (  9 + 81 + 19 * 94 / (  0 * 71 + 53 - 20 * 94  )  )  ) ", answer: "", err: errors.New("typeError: division by zero")},
		{expr: " (  96 / 83 - 53 - (  59 - 91 / 91 - 54  )  ) / (  75 + 4 / (  50 - 80 * 45 + 93 + 18  ) - 76 / 54  ) * 14 + 59 ", answer: "48.376380", err: nil},
		{expr: " 59 - 13 + (  25 * 22 / (  47 / 38 * (  64 / 93 - 91 + 72  ) * 66  ) + 43 - 5  ) * 39 / 55 ", answer: "72.684566", err: nil},
	}

	for _, c := range tSuite {
		result, err := CalculateExpression(c.expr)
		assert.Equal(t, c.err, err)
		assert.Equal(t, c.answer, result)
	}
}
