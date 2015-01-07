/*
Input:
a: a whole, positive number

Output:
plus5: a number that is the sum of 5 and `a`
asString: a string that is just `a` converted to a string
asStringWithFoo: a string that is `a` with the string 'foo' appended
a: the original a number
*/
function variableModification(a) {
  var plus5;
  var asString;
  var asStringWithFoo;
  //your code here
  plus5 = a + 5;
  asString = String(a);
  asStringWithFoo = a + 'foo';
  return [plus5, asString, asStringWithFoo, a];
  //end your code
}

/*
Input:
b: could be anything

Output:
return true if b is a primitive string value, false otherwise
*/
function isString(b) {
  //your code here
  if (typeof b == 'string') {
    return true;
  }
  else {
    return false;
  }
  //end your code
}

/*
Input:
c: could be anything

Output:
return true if c is undefined, false otherwise
*/
function isUndefined(c) {
  //your code here
  if (typeof c === 'undefined') {
    return true;
  }
  else {
    return false;
  }
  //end your code
}
