    void decision_k(){
        if(isHomogenous()) {
            cout << "terminated" << endl;
            decision = dominant;
        }else if(data_size<=k){
            cout << "terminated" << endl;
            if(dominant!="equal")
                decision = dominant;
                //look one level ahead and return the result
            else{
                if(this->previous_state->dominant!="equal"){
                    decision = dominant;
                }
                else{
                    decision = "no_recurrence-events";
                }
            }
        }else{
            //todo find all children correspoding to an attribute values
            ch_number = (int)table_yes_no[bestGainColumn].size();
//            int counter = 0 ;
            for (auto it = table_yes_no[bestGainColumn].begin(); it != table_yes_no[bestGainColumn].end(); it++) {
//                next_states.push_back( new State(this,it->first));
                cout << "split attribute: " << it->first << endl;
                children[it->first] = new State(this,it->first);
            }
        }
    }
