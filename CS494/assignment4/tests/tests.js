asyncTest('Testing GET request with empty paramaters variable"', function(assert) {
	var result = ajaxRequest('http://classes.engr.oregonstate.edu/eecs/fall2014/cs494-400/tools/loopback.php', 'GET', {});
	setTimeout(function() {
		assert.deepEqual(result, {response: '{"RequestType":"GET","GetVariables":[],"PostVariables":[]}', code: 200, codeDetail: "OK", success: true}, "Correct return of empty paramaters variable");
		QUnit.start();
}, 500)});

asyncTest('Testing GET request with populated paramaters variable"', function(assert) {
	var result = ajaxRequest('http://classes.engr.oregonstate.edu/eecs/fall2014/cs494-400/tools/loopback.php', 'GET', {foo:'bar', baz:'bop', fizz:'42'});
	setTimeout(function() {
		assert.deepEqual(result, {response: '{"RequestType":"GET","GetVariables":{"foo":"bar","baz":"bop","fizz":"42"},"PostVariables":[]}', code: 200, codeDetail: "OK", success: true}, "Correct return of populated paramaters variable");
		QUnit.start();
}, 500)});

asyncTest('Testing GET request with server failure"', function(assert) {
	var result = ajaxRequest('http://classes.engr.oregonstate.edu/eecs/fall2014/cs494-400/tools/error418.php', 'GET', {foo:'bar', baz:'bop', fizz:'42'});
	setTimeout(function() {
		assert.equal(result.code, 418, "Returns proper code");
		assert.equal(result.codeDetail, 'I\'m a Teapot', "Returns proper code text");
		assert.equal(result.success, false, "Properly returns failure");
		QUnit.start();
}, 500)});

asyncTest('Testing POST request with empty paramaters variable"', function(assert) {
	var result = ajaxRequest('http://classes.engr.oregonstate.edu/eecs/fall2014/cs494-400/tools/loopback.php', 'POST', {});
	setTimeout(function() {
		assert.deepEqual(result, {response: '{"RequestType":"POST","GetVariables":[],"PostVariables":[]}', code: 200, codeDetail: "OK", success: true}, "Correct return of empty paramaters variable");
		QUnit.start();
}, 500)});

asyncTest('Testing POST request with populated paramaters variable"', function(assert) {
	var result = ajaxRequest('http://classes.engr.oregonstate.edu/eecs/fall2014/cs494-400/tools/loopback.php', 'POST', {foo:'bar', baz:'bop', fizz:'42'});
	setTimeout(function() {
		assert.deepEqual(result, {response: '{"RequestType":"POST","GetVariables":[],"PostVariables":{"foo":"bar","baz":"bop","fizz":"42"}}', code: 200, codeDetail: "OK", success: true}, "Correct return of populated paramaters variable");
		QUnit.start();
}, 500)});

asyncTest('Testing POST request with server failure"', function(assert) {
	var result = ajaxRequest('http://classes.engr.oregonstate.edu/eecs/fall2014/cs494-400/tools/error418.php', 'POST', {foo:'bar', baz:'bop', fizz:'42'});
	setTimeout(function() {
		assert.equal(result.code, 418, "Returns proper code");
		assert.equal(result.codeDetail, 'I\'m a Teapot', "Returns proper code text");
		assert.equal(result.success, false, "Properly returns failure");
		QUnit.start();
}, 500)});