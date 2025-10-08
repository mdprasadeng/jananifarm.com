
Array.prototype.random = function () {
  return this[Math.floor((Math.random()*this.length))];
}

Array.prototype.removeByValue = function(value) {
  for (let i = 0; i < this.length; i++) {
    if (this[i] === value) {
      this.splice(i, 1);
      i--; // Adjust index after removal to re-check the current position
    }
  }
  return this; // Return the modified array for chaining
};

let puzzle_text = `6x6
1:-4,2:-4,3:-1,4:+12,5:/3,6:*60,7:+8,8:+1,9:/2,A:+9,B:+7,C:+10,D:*300,E:+8,F:/3
112233
455678
446677
9ABCCD
9ABBDD
EEEFFD`

function generate_answer(text) {
    let lines = text.split("\n")
    let size = parseInt(lines[0].split("x"))
    
    let rules_txt = lines[1].split(",")
    let rules = {}
    let rule_indexes = {}
    for (const rule_text of rules_txt) {
        let rule_text_split = rule_text.split(":")
        rules[rule_text_split[0]] = rule_text_split[1]
        rule_indexes[rule_text_split[0]] = []
    }

    let rule_labels = new Array(size*size);
    for(let i=2; i < 2 + size; i ++) {
        let rule_grid = lines[i].split("")
        for(let r=0; r<size; r++) {
            rule_indexes[rule_grid[r]].push((i-2)*size + r);
            rule_labels[(i-2)*size + r] = rule_grid[r]
        }
    }


    let valids = new Array(size*size);
    let answer = new Array(size*size);
    for(let i=0; i<size*size; i++) {
        valids[i] = []
        for(let j=0; j<size; j++) {
            valids[i].push(j+1);
        }
        answer[i] = 0;
    }

    let guessAt = 0;
    let solution_impossible = false
    let loop_breaker = 0;
    while(guessAt < size*size ) {
        
        //loop breaker
        loop_breaker++;
        if (loop_breaker > 99999) {
            break;
        } 

        //fail state
        if (solution_impossible) {
            console.log("no solution", valids);
            return undefined;
        }

        //backtracking
        if (valids[guessAt].length == 0) {
            guessAt--;
            if (guessAt < 0) {
                solution_impossible = true;
                continue
            }
            valids[guessAt].removeByValue(answer[guessAt]);
            valids[guessAt+1] = []
            for(let j=0; j<size; j++) {
                valids[guessAt+1].push(j+1)
            }
            
            answer[guessAt] = 0;            
            continue;
        }

        //guess
        answer[guessAt] = valids[guessAt].random();
        
        //check all in same row and col
        let col = guessAt % size;
        let row = (guessAt - col) ;
        let validGuess = true
        for (let i=0; i<size ; i++) {
            let coli = col + i*size;
            let rowi = row + i;
            if ( 
                (coli != guessAt && answer[guessAt] == answer[coli]) //something else in column is same
                || 
                (rowi != guessAt && answer[guessAt] == answer[rowi]) //something else in row is same    
            ) {
                valids[guessAt].removeByValue(answer[guessAt]);
                answer[guessAt] = 0;
                validGuess = false;
                break;
            }

        }

        let rule_label = rule_labels[guessAt]
        let rule = rules[rule_label];
        let rule_locations = rule_indexes[rule_label];
        let computed_value = 0;
        let expected_value = parseInt(rule.substr(1));
        for (const rule_location of rule_locations) {
            if (answer[rule_location] > 0) {
                switch (rule[0]) {
                    case "+":
                        computed_value += answer[rule_location];
                        break;
                    case "-":
                        if (computed_value == 0) {
                            computed_value = answer[rule_location];
                        } else {
                            computed_value = Math.abs(computed_value - answer[rule_location]);
                        }
                        break;
                    case "*":
                        if (computed_value == 0) {
                            computed_value = 1;
                        }
                        computed_value *= answer[rule_location];
                        break;
                    case "/":
                        if (computed_value == 0) {
                            computed_value = answer[rule_location];
                        } else {
                            if (computed_value > answer[rule_location]) {
                                computed_value = computed_value / answer[rule_location];
                            } else {
                                computed_value = answer[rule_location] / computed_value;    
                            }
                            
                        }
                        break;
                }    
            } else {
                computed_value = expected_value;
                break;
            }
        }

        if (computed_value != expected_value) {
            valids[guessAt].removeByValue(answer[guessAt]);
                answer[guessAt] = 0;
                validGuess = false;    
        }
        

        if (validGuess) {
            guessAt++;
        }

    }
    
    return answer;
}

console.log(generate_answer(puzzle_text))