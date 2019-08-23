class Evote {
  constructor(baseUrl) {
    this.baseUrl = "http://localhost:5000/api"

  }

  createUser(userObj, faceBlob, profileBlob) {
    var data = new FormData();
    for (const key in userObj) {
      data.append(key, userObj[key])
    }
    data.append("profilePhoto", profileBlob);
    data.append("facePhoto", faceBlob)
    return this.callUrl('POST', "/voters/create", data);
  }

  authenticateUserAsync(faceBlob, userIdfromBarcode) {
    var formdata = new FormData();
    formdata.append("userId", userIdfromBarcode);
    formdata.append("queryFace", faceBlob);
    return this.callUrl('POST', "auth", formdata)
  }

  getElections() {
    return this.callUrl('GET', 'elections', null)
  }

  getCandidates(electionId) {
    return this.callUrl('GET', `/election/${electionId.toString()}`, null);
  }

  vote(userId, candidateToVote, electionType) {
    let formdata = new FormData()
    formdata.append('userId', userId);
    formdata.append('candidateId', candidateToVote)
    formdata.append('electiontype', electionType)
    return this.callUrl('POST', '/voters/vote', formdata);
  }

  callUrl(method,url, formdata){
    let request = new Request(this.baseUrl+url, {
      method : method,
      body : formdata
    })
    return new Promise((res, rej) => {
      fetch(request).then(resp => {
        resp.data = resp.json();
        res(resp)
      }).catch(e => rej(e))
    })
  }
}

export default Evote;
