// // triangle print code

// auto triangles = TriangleCount::countTriangles(csr);

// cout<<"Algorithm: Triangle Counting\n";

// cout<<"Total triangles: "
//     <<triangles.size()
//     <<"\n\n";

// cout<<"Triangles found:\n";

// for(auto &t : triangles)
// {
//     cout<<"("
//         <<get<0>(t)<<", "
//         <<get<1>(t)<<", "
//         <<get<2>(t)
//         <<")\n";
// }

// cout<<"\nExecution time: "<<time<<" ms\n";


// connected component print sequence

// vector<int> component;

// int totalComponents =
//     ConnectedComponents::findComponents(csr, component);

// cout << "Algorithm : Connected Components\n\n";

// cout << "Number of Connected Components : "
//      << totalComponents
//      << "\n\n";

// cout << "Vertex\tComponent\n";

// for(int i = 0; i < component.size(); i++)
// {
//     cout << i
//          << "\t"
//          << component[i]
//          << endl;
// }

// Execution time using chrono later